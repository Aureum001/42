/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:19:51 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/20 16:25:22 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex_number(t_print *tab, unsigned long long n,
						int uppercase, int zero_pad)
{
	int	prefix_len;

	prefix_len = ft_handle_hex_prefix(tab, n, uppercase);
	ft_print_zeros(zero_pad);
	ft_putnbr_base(n, 16, uppercase);
}

int	ft_print_perc(t_print *tab)
{
	write(1, "%", 1);
	tab->total_length += 1;
	return (1);
}
