/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:22:39 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 21:22:39 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	const char	*initial;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (start--)
		s++;
	i = 0;
	initial = s;
	while (*s && i < len)
	{
		s++;
		i++;
	}
	str = (char *)malloc(sizeof(*s) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, initial, i + 1);
	return (str);
}