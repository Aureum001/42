/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:51:03 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/03 20:51:03 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t mem, size_t n)
{
	void	*res;
	size_t	max;

	max = ~0;
	if (mem && n > max / mem)
	{
		return (NULL);
	}
	res = malloc(mem * n);
	if (res)
		ft_bzero(res, mem * n);
	return (res);
}
