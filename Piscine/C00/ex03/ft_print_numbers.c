/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:09:12 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/04 12:12:02 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_numbers(void)
{
	int		counter;
	char	number;

	counter = 0;
	while (counter <= 9)
	{
		number = '0' + counter;
		ft_putchar(number);
		counter++;
	}
}
