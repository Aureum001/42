/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:12:22 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 21:12:22 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	len;

	len = ft_strlen(src);
	str = (char *)malloc(sizeof(*src) * (len + 1));
	if (!str)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(str, src, len + 1);
	return (str);
}