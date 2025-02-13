/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:18:08 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/06 18:45:26 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 32) && (str[i] <= 126)))
			write(1, ".", 1);
		else
			write(1, str + i, 1);
		i++;
	}
}

void	print_address(void *ptr)
{
	long	addr;
	char	*hex_digits;
	char	address_str[16];
	int		i;

	addr = (long)ptr;
	hex_digits = "0123456789abcdef";
	i = 15;
	while (i >= 0)
	{
		address_str[i] = hex_digits[addr % 16];
		addr /= 16;
		i--;
	}
	write(1, address_str, 16);
	write(1, ": ", 2);
}

void	print_hex_char(unsigned char c)
{
	char	*hex_digits;
	char	hex_str[2];

	hex_digits = "0123456789abcdef";
	hex_str[0] = hex_digits[c / 16];
	hex_str[1] = hex_digits[c % 16];
	write(1, hex_str, 2);
}

void	print_second_column(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (i % 2 == 1)
		{
			print_hex_char(ptr[i]);
			write(1, " ", 1);
		}
		else
			print_hex_char(ptr[i]);
		i++;
	}
	while (16 - i > 0)
	{
		write(1, " ", 1);
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	int		i;
	char	*ptr;

	ptr = (char *)addr;
	i = 0;
	if (size == 0)
		return (addr);
	print_address(addr);
	print_second_column(ptr);
	ft_putstr(ptr);
	return (addr);
}
