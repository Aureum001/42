/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:37:39 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 19:37:39 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	if (!*s2)
		return ((char *)s1);
	while (*s1 && n)
	{
		if (*s1 == *s2)
		{
			i = 0;
			while (s2[i]
				&& s1[i] == s2[i]
				&& i < n)
				i++;
			if (!s2[i])
				return ((char *)s1);
		}
		n--;
		s1++;
	}
	return (NULL);
}
