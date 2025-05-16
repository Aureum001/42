/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:38:44 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/16 18:27:20 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_string_padding(t_print *tab, char *str,
								int len, int padding)
{
	if (tab->dash)
	{
		write(1, str, len);
		ft_print_padding(padding);
	}
	else
	{
		ft_print_padding(padding);
		write(1, str, len);
	}
}

static int	ft_print_null(t_print *tab)
{
	int		len;
	int		padding;
	char	*null_str;

	null_str = "(null)";
	if (tab->point)
	{
		if (tab->precision < 6)
		{
			ft_print_padding(tab->width);
			tab->total_length += tab->width;
			return (tab->width);
		}
	}
	len = 6;
	if (tab->point && tab->precision < len)
		len = tab->precision;
	if (tab->width > len)
		padding = tab->width - len;
	else
		padding = 0;
	ft_print_string_padding(tab, null_str, len, padding);
	tab->total_length += len + padding;
	return (len + padding);
}

int	ft_print_s(t_print *tab)
{
	char	*str;
	int		len;
	int		padding;

	str = va_arg(tab->args, char *);
	if (!str)
	{
		return (ft_print_null(tab));
	}
	len = ft_strlen(str);
	if (tab->point && tab->precision < len)
		len = tab->precision;
	padding = 0;
	if (tab->width > len)
		padding = tab->width - len;
	ft_print_string_padding(tab, str, len, padding);
	tab->total_length += len + padding;
	return (len + padding);
}
