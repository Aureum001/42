/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:20:47 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/13 16:35:57 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dest_len;

	dest_len = ft_strlen(dest);
	j = dest_len;
	i = 0;
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while ((src[i]) && (i < size - dest_len - 1))
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest_len + ft_strlen(src));
}
