/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:20:48 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 19:20:48 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len && *(str + len) != (char)c)
		len--;
	if (*(str + len) == (char)c)
		return ((char *)(str + len));
	return (NULL);
}