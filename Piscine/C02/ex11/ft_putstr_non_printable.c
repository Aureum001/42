/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:30:19 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/06 18:45:57 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_hex(int dec)
{
	char	hex[3];
	int		i;
	int		remainder;

	i = 0;
	if (dec == 0)
	{
		hex[i++] = 0;
		hex[i++] = 0;
	}
	while (dec > 0)
	{
		remainder = dec % 16;
		if (remainder < 10)
			hex[i++] = remainder + '0';
		else
			hex[i++] = remainder - 10 + 'a';
		dec = dec / 16;
	}
	if (i == 1)
		ft_putchar('0');
	while (--i >= 0)
	{
		ft_putchar(hex[i]);
	}
}

void	ft_putstr_non_printable(char *str)
{
	int		i;
	int		ascii;

	i = 0;
	while (str[i])
	{
		if (((str[i] < 32) || (str[i] > 126)))
		{
			ascii = str[i];
			ft_putchar('\\');
			print_hex(ascii);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}
