/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:26:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 18:26:20 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*buf;

	if (!dst || !src)
		return (0);
	buf = src;
	if (src && dst && size)
	{
		while (*src && --size)
			*dst++ = *src++;
		*dst = 0;
	}
	return (ft_strlen(buf));
}
