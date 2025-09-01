/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:38:42 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:19:52 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(t_print *tab)
{
	int	c;
	int	padding;

	c = va_arg(tab->args, int);
	padding = 0;
	tab->point = 0;
	tab->precision = 0;
	if (tab->width > 1)
		padding = tab->width - 1;
	if (tab->dash)
	{
		write(1, &c, 1);
		ft_print_padding(padding);
	}
	else
	{
		ft_print_padding(padding);
		write(1, &c, 1);
	}
	tab->total_length += padding + 1;
	return (padding + 1);
}
