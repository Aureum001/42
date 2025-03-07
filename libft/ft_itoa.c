/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:09:09 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/04 13:09:09 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_digits(long long n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static void	num_str(char *str, long long n, size_t digits)
{
	char	*base;

	base = "0123456789";
	if (n == 0)
		*str = '0';
	else if (n < 0)
	{
		while(digits > 1)
		{
			*(str + digits - 1) = base[-(n % 10)];
			n /= 10;
			digits--;
		}
		*str = '-';
	}
	else
	{
		while(digits > 0)
		{
			*(str + digits - 1) = base[n % 10];
			n /= 10;
			digits--;
		}
	}	
}
char	*ft_itoa(int n)
{
	char		*str;
	long long	n_long;
	size_t		digits;

	n_long = (long long)n;
	digits = n_digits(n_long);
	if (n < 0)
		digits++;	
	str = (char *)malloc(sizeof(*str) * (digits + 1));
	if(!str)
		return (NULL);
	num_str(str, n_long, digits);
	*(str + digits) = '\0';
	return (str);
}