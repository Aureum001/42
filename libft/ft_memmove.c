/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:06:24 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 17:06:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	dst_cpy = (unsigned char *)dst;
	src_cpy = (unsigned char *)src;
	i = n - 1;
	if (src_cpy < dst_cpy)
	{
		while (i >= 0)
		{
			dst_cpy[i] = src_cpy[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
