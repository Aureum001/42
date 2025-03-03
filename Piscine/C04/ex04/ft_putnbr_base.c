/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:50:41 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/15 11:45:35 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	check_base_condition(char *base)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[a] != '\0')
	{
		b = a + 1;
		if (base[a] == '+' || base[a] == '-')
			return (0);
		if (base[a] < ' ' || base[a] > '~')
			return (0);
		while (base[b] != '\0')
		{
			if (base[a] == base[b])
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

void	ft_putmaxneg_base(int nbr, char *base)
{
	if (nbr <= (-1 * ft_strlen(base)))
	{
		ft_putmaxneg_base(nbr / ft_strlen(base), base);
		ft_putmaxneg_base(nbr % ft_strlen(base), base);
	}
	else
		ft_putchar(base[-nbr]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	if (check_base_condition(base))
	{
		if (nbr == -2147483648)
		{
			ft_putchar('-');
			ft_putmaxneg_base(nbr, base);
			return ;
		}
		if (nbr < 0)
		{
			ft_putchar('-');
			nbr = -nbr;
		}
		if (nbr >= ft_strlen(base))
		{
			ft_putnbr_base(nbr / ft_strlen(base), base);
			ft_putnbr_base(nbr % ft_strlen(base), base);
		}
		else
			ft_putchar(base[nbr]);
	}
}
