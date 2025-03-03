/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:22:45 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/18 18:04:23 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str);
int	c_in_base(char c, char *base);
int	ft_num_digits(int nbr, int base_len);
int	check_base_condition(char *base);
int	skip_whitespace_and_sign(char *nbr, int *sign);

char	*ft_allocate_result(int nbr, char *base_to)
{
	int	base_len;
	int	digits;

	base_len = ft_strlen(base_to);
	digits = ft_num_digits(nbr, base_len);
	return ((char *)malloc(digits + 2));
}

void	ft_putmaxneg_base(int nbr, char *base, char *result, int *index)
{
	if (nbr <= (-1 * ft_strlen(base)))
	{
		ft_putmaxneg_base(nbr / ft_strlen(base), base, result, index);
		ft_putmaxneg_base(nbr % ft_strlen(base), base, result, index);
	}
	else
		result[(*index)++] = base[-nbr];
}

void	ft_putnbr_base(int nbr, char *base, char *result, int *index)
{
	if (nbr == -2147483648)
	{
		result[(*index)++] = '-';
		ft_putmaxneg_base(nbr, base, result, index);
		return ;
	}
	if (nbr < 0)
	{
		result[(*index)++] = '-';
		nbr = -nbr;
	}
	if (nbr >= ft_strlen(base))
	{
		ft_putnbr_base(nbr / ft_strlen(base), base, result, index);
		ft_putnbr_base(nbr % ft_strlen(base), base, result, index);
	}
	else
		result[(*index)++] = (base[nbr]);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		i;
	int		sign;
	int		res;
	char	*str;
	int		index;

	if (check_base_condition(base_from) && check_base_condition(base_to))
	{
		index = 0;
		res = 0;
		i = 0;
		sign = 1;
		i = skip_whitespace_and_sign(nbr, &sign);
		while (c_in_base(nbr[i], base_from) >= 0)
			res = res * ft_strlen(base_from) + c_in_base(nbr[i++], base_from);
		str = ft_allocate_result(res * sign, base_to);
		if (!str)
			return (NULL);
		ft_putnbr_base(res * sign, base_to, str, &index);
		str[index] = '\0';
		return (str);
	}
	else
		return (NULL);
}
