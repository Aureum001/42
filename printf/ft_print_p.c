/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:47:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/12 17:21:16 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_ptr_value(t_print *tab, unsigned long long ptr_val,
								int numlen, int padding)
{
	if (tab->dash)
	{
		write(1, "0x", 2);
		ft_putnbr_base(ptr_val, 16, 0);
		ft_print_padding(padding);
	}
	else
	{
		ft_print_padding(padding);
		write(1, "0x", 2);
		ft_putnbr_base(ptr_val, 16, 0);
	}
	return (numlen + 2 + padding);
}

static int	ft_print_null_p(t_print *tab)
{
	char	*null_str;
	int		len;
	int		padding;

	null_str = "(nil)";
	len = 5;
	padding = 0;
	if (tab->width > len)
		padding = tab->width - len;
	if (tab->dash)
	{
		write(1, null_str, len);
		ft_print_padding(padding);
	}
	else
	{
		ft_print_padding(padding);
		write(1, null_str, len);
	}
	tab->total_length += len + padding;
	return (len + padding);
}

int	ft_print_p(t_print *tab)
{
	void				*ptr;
	unsigned long long	ptr_val;
	int					numlen;
	int					padding;
	int					total_len;

	ptr = va_arg(tab->args, void *);
	if (!ptr)
		return (ft_print_null_p(tab));
	ptr_val = (unsigned long long)ptr;
	padding = 0;
	numlen = ft_get_numlen(ptr_val, 16);
	if (tab->width > numlen + 2)
		padding = tab->width - (numlen + 2);
	total_len = ft_print_ptr_value(tab, ptr_val, numlen, padding);
	tab->total_length += total_len;
	return (total_len);
}
