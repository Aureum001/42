/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:19:51 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:17:28 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex_number(t_print *tab, unsigned long long n,
						int uppercase, int zero_pad)
{
	int	prefix_len;

	prefix_len = ft_handle_hex_prefix(tab, n, uppercase);
	ft_print_zeros(zero_pad);
	ft_putnbr_base(n, 16, uppercase);
}
