/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:39:59 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/04 12:21:25 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_comb2(void)
{
	int		first;
	int		second;
	char	a;

	first = 0;
	while (first < 99)
	{
		second = first + 1;
		while (second < 100)
		{
			a = first / 10 + '0';
			ft_putchar(a);
			a = first % 10 + '0';
			ft_putchar(a);
			ft_putchar(' ');
			a = second / 10 + '0';
			ft_putchar(a);
			a = second % 10 + '0';
			ft_putchar(a);
			if (!(first == 98 && second == 99))
				write(1, ", ", 2);
			second++;
		}
		first++;
	}
}
