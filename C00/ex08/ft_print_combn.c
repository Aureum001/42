/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:30:59 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/04 12:41:51 by ancanale         ###   ########.fr       */
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

void	print_combination(int arr[], int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ft_putnbr(arr[i]);
		i++;
	}
}

void	increment_combination(int arr[], int n)
{
	int		i;
								
	i = n - 1;
	while (i >= 0)
	{
		if (arr[i] < 9 - (n - 1 - i))
		{
			arr[i]++;
			while (++i < n)
				arr[i] = arr[i - 1] + 1;
			break ;
		}
		i--;
	}
}

void	ft_print_combn(int n)
{
	int		arr[10];
	int		i;

	i = 0;
	if (n <= 0 || n > 10)
		return ;
	while (i < n)
	{
		arr[i] = i;
		i++;
	}
	while (arr[0] < 10 - n)
	{
		print_combination(arr, n);
		if (arr[0] != 10 - n)
			write(1, ", ", 2);
		increment_combination(arr, n);
	}
	print_combination(arr, n);
}
