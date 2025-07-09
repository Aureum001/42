/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:46:13 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:19:50 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_print_i(t_print *tab)
{
	int	num;

	num = va_arg(tab->args, int);
	return (ft_format_integer(tab, num, 1));
}
