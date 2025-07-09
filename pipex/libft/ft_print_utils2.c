/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:14:28 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:19:50 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_zeros(int count)
{
	while (count-- > 0)
		write(1, "0", 1);
}

void	ft_putnbr_base(unsigned long long n, int base, int uppercase)
{
	char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (n >= (unsigned long long)base)
		ft_putnbr_base(n / base, base, uppercase);
	write(1, &digits[n % base], 1);
}

int	ft_calculate_padding(t_print *tab, int numlen, int sign, int *zero_pad)
{
	int	total_len;
	int	width_pad;

	*zero_pad = 0;
	if (tab->point && tab->precision > numlen)
		*zero_pad = tab->precision - numlen;
	else if (tab->zero && !tab->dash && !tab->point)
	{
		if (tab->width > numlen + sign)
			*zero_pad = tab->width - numlen - sign;
		else
			*zero_pad = 0;
	}
	total_len = numlen + *zero_pad + sign;
	width_pad = 0;
	if (tab->width > total_len && (!tab->zero || tab->dash || tab->point))
		width_pad = tab->width - total_len;
	return (width_pad);
}

int	ft_format_integer(t_print *tab, long long n, int is_signed)
{
	int			numlen;
	int			zero_pad;
	int			width_pad;
	int			total_len;
	int			sign;

	if (ft_handle_zero_precision(tab, n))
		return (tab->width);
	sign = ft_handle_sign(tab, n, is_signed);
	if (n < 0)
		n = -n;
	numlen = ft_get_numlen(n, 10);
	width_pad = ft_calculate_padding(tab, numlen, sign, &zero_pad);
	total_len = numlen + zero_pad + sign;
	if (!tab->dash)
		ft_print_padding(width_pad);
	ft_print_integer(tab, n, sign, zero_pad);
	if (tab->dash)
		ft_print_padding(width_pad);
	tab->total_length += total_len + width_pad;
	return (total_len + width_pad);
}

int	ft_format_hex(t_print *tab, unsigned long long n, int uppercase)
{
	int	numlen;
	int	zero_pad;
	int	width_pad;
	int	total_len;
	int	prefix_len;

	if (ft_handle_zero_precision(tab, n))
		return (tab->width);
	if (tab->hash && n != 0)
		prefix_len = 2;
	else
		prefix_len = 0;
	numlen = ft_get_numlen(n, 16);
	width_pad = ft_calculate_padding(tab, numlen + prefix_len, 0, &zero_pad);
	total_len = numlen + zero_pad + prefix_len;
	if (!tab->dash)
		ft_print_padding(width_pad);
	ft_print_hex_number(tab, n, uppercase, zero_pad);
	if (tab->dash)
		ft_print_padding(width_pad);
	tab->total_length += total_len + width_pad;
	return (total_len + width_pad);
}
