/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:10:03 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:17:31 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print	*ft_initialise_tab(t_print *tab)
{
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->sign = 0;
	tab->total_length = 0;
	tab->zero = 0;
	tab->dash = 0;
	tab->percent = 0;
	tab->space = 0;
	tab->hash = 0;
	tab->plus = 0;
	return (tab);
}

void	ft_reset_flags(t_print *tab)
{
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->dash = 0;
	tab->sign = 0;
	tab->percent = 0;
	tab->space = 0;
	tab->hash = 0;
	tab->plus = 0;
}

int	ft_is_flag(char c)
{
	return (c == '-' || c == '.' || (
			c >= '0' && c <= '9') || c == ' '
		|| c == '+' || c == '#');
}

int	ft_print_padding(int padding)
{
	int	i;

	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

int	ft_get_numlen(unsigned long long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
