/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:58:18 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/29 10:27:51 by ancanale         ###   ########.fr       */
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

static int	ft_parse_simple_flags(t_print *tab, char const *format, int j)
{
	if (format[j] == '+')
	{
		tab->plus = 1;
		tab->space = 0;
	}
	else if (format[j] == ' ')
		tab->space = 1;
	else if (format[j] == '#')
		tab->hash = 1;
	return (j + 1);
}

int	ft_parse_flag(t_print *tab, char const *format, int j)
{
	if (format[j] == '-')
	{
		tab->zero = 0;
		tab->dash = 1;
		while (format[j] == '-')
			j++;
		return (j);
	}
	else if (format[j] == '0' && !tab->point)
	{
		tab->zero = 1;
		while (format[j] == '0')
			j++;
		return (j);
	}
	else if (format[j] == '.')
		return (tab->zero = 0, ft_parse_precision(tab, format, j));
	else if (format[j] >= '0' && format[j] <= '9')
	{
		while (format[j] >= '0' && format[j] <= '9')
			tab->width = tab->width * 10 + (format[j++] - '0');
		return (j);
	}
	return (ft_parse_simple_flags(tab, format, j));
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
