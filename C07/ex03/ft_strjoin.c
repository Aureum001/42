/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:53:54 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/13 18:21:27 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;
	
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	calc_tlen(int size, char **strs, char *sep)
{
	int	total_len;
	int	sep_len;
	int	i;

	i = 0;
	total_len = 0;
	sep_len = 0;
	sep_len = ft_strlen(sep);
	while (i < size)
	{
		total_len += ft_strlen(strs[i]);
		i++;
		if (i < size - 1)
			total_len += sep_len;
	}
	return total_len;
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*result;
	int		total_len;

	if (size == 0)
	{
		result = (char*)malloc(size + 1);
		result[0] = '\0';
		return (result);
	}
	int total_len = calc_tlen(size, strs, sep);	
	result = (char*)malloc(total_len + 1);
	if (!result)
		return NULL;
}