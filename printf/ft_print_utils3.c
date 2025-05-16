/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:37:17 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/16 17:29:07 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_sign(t_print *tab, long long n, int is_signed)
{
	int	sign;

	sign = 0;
	if (is_signed && n < 0)
	{
		sign = 1;
		tab->sign = '-';
	}
	else if (is_signed && tab->plus)
	{
		sign = 1;
		tab->sign = '+';
	}
	else if (is_signed && tab->space)
	{
		sign = 1;
		tab->sign = ' ';
	}
	return (sign);
}

int	ft_handle_hex_prefix(t_print *tab, unsigned long long n, int uppercase)
{
	if (tab->hash && n != 0)
	{
		if (uppercase)
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
		return (2);
	}
	return (0);
}

int	ft_handle_zero_precision(t_print *tab, long long n)
{
	if (tab->point && tab->precision == 0 && n == 0)
	{
		ft_print_padding(tab->width);
		tab->total_length += tab->width;
		return (1);
	}
	return (0);
}

void	ft_print_integer(t_print *tab, long long n, int sign, int zero_pad)
{
	if (sign)
		write(1, &tab->sign, 1);
	ft_print_zeros(zero_pad);
	ft_putnbr_base(n, 10, 0);
}

int	ft_eval_format(t_print *tab, char const *format, int i)
{
	int	j;

	j = i;
	while (format[j] && ft_is_flag(format[j]))
		j = ft_parse_flag(tab, format, j);
	if (format[j] == 's')
		ft_print_s(tab);
	else if (format[j] == 'd' || format[j] == 'i')
		ft_print_d(tab);
	else if (format[j] == 'u')
		ft_print_u(tab);
	else if (format[j] == 'X')
		ft_print_hex(tab, 1);
	else if (format[j] == 'x')
		ft_print_hex(tab, 0);
	else if (format[j] == 'c')
		ft_print_c(tab);
	else if (format[j] == 'p')
		ft_print_p(tab);
	else if (format[j] == '%')
		ft_print_perc(tab);
	return (j);
}
