/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:29:02 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/04 12:24:55 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	char	a;
	int		divisor;
	int		aux;

	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	divisor = 1;
	aux = nb;
	while (aux >= 10)
	{
		aux = aux / 10;
		divisor = divisor * 10;
	}
	while (divisor > 0)
	{
		a = '0' + nb / divisor;
		ft_putchar(a);
		nb = nb % divisor;
		divisor = divisor / 10;
	}
}
