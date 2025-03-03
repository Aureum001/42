/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:14:53 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/18 17:44:38 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	c_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_num_digits(int nbr, int base_len)
{
	int	digits;

	digits = 0;
	if (nbr <= 0)
		digits = 1;
	while (nbr)
	{
		nbr /= base_len;
		digits++;
	}
	return (digits);
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

int	skip_whitespace_and_sign(char *nbr, int *sign)
{
	int	i;

	i = 0;
	while ((nbr[i] == ' ') || (nbr[i] >= '\t' && nbr[i] <= '\r'))
		i++;
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}
