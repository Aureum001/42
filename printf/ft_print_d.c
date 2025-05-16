/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:47:27 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/12 16:15:50 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h" 

int	ft_print_d(t_print *tab)
{
	int	num;

	num = va_arg(tab->args, int);
	return (ft_format_integer(tab, num, 1));
}
