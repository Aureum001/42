/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:31:55 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:19:50 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(t_print *tab, int kind)
{
	unsigned int	num;

	num = va_arg(tab->args, unsigned int);
	return (ft_format_hex(tab, num, kind));
}
