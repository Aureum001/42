/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:58:42 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:44 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_cleanup(t_print *tab, int ret)
{
	va_end(tab->args);
	ret += tab->total_length;
	free(tab);
	return (ret);
}

int	ft_print_perc(t_print *tab)
{
	if (tab->width > 1 && !tab->dash)
		ft_print_padding(tab->width - 1);
	write(1, "%", 1);
	if (tab->width > 1 && tab->dash)
		ft_print_padding(tab->width - 1);
	if ((tab->width > 1))
	{
		tab->total_length += tab->width;
		return (tab->width);
	}
	else
	{
		tab->total_length += 1;
		return (1);
	}
}

// int ft_print_perc(t_print *tab)
// {
//     write(1, "%", 1);
//     tab->total_length += 1;
//     return (1);
// }

static int	ft_parse_precision(t_print *tab, char const *format, int j)
{
	tab->point = 1;
	j++;
	while (format[j] >= '0' && format[j] <= '9')
	{
		tab->precision = tab->precision * 10 + (format[j] - '0');
		j++;
	}
	return (j);
}

int	ft_parse_flag(t_print *tab, char const *format, int j)
{
	if (format[j] == '-')
		tab->dash = 1;
	else if (format[j] == '+')
		tab->plus = 1;
	else if (format[j] == ' ')
		tab->space = 1;
	else if (format[j] == '#')
		tab->hash = 1;
	else if (format[j] == '0' && !tab->point)
		tab->zero = 1;
	else if (format[j] == '.')
		return (ft_parse_precision(tab, format, j));
	else if (format[j] >= '0' && format[j] <= '9')
	{
		while (format[j] >= '0' && format[j] <= '9')
		{
			tab->width = tab->width * 10 + (format[j] - '0');
			j++;
		}
		return (j);
	}
	return (j + 1);
}

int	ft_printf(char const *format, ...)
{
	t_print	*tab;
	int		i;
	int		ret;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	ft_initialise_tab(tab);
	va_start(tab->args, format);
	i = -1;
	ret = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			ft_reset_flags(tab);
			i = ft_eval_format(tab, format, i + 1);
			if (!format[i])
				break ;
		}
		else
			ret += write(1, &format[i], 1);
	}
	return (ft_handle_cleanup(tab, ret));
}
