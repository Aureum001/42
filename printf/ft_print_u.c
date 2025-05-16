/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:48:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/12 16:16:06 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h" 

int	ft_print_u(t_print *tab)
{
	unsigned int	num;

	num = va_arg(tab->args, unsigned int);
	return (ft_format_integer(tab, num, 0));
}
