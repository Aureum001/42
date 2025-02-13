/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:14:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/12 19:15:31 by ancanale         ###   ########.fr       */
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

int	char_in_base(char c, char *base)
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

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		sign;
	int		result;
	int		r_i;
	int		base_len;

	result = 0;
	base_len = ft_strlen(base);
	r_i = 0;
	i = 0;
	sign = 1;
	while (str[i] >= '\a' && str[i] <= '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (char_in_base(str[i], base) >= 0)
	{
		r_i = char_in_base(str[i++], base);
		result = result * base_len + r_i;
	}
	return (result * sign);
}
