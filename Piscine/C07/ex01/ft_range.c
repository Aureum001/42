/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:04:12 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/11 18:16:43 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	*range;

	if (min >= max)
		return (NULL);
	range = malloc(sizeof(int) * (max - min));
	if (!(range))
		return (NULL);
	i = 0;
	while (max - 1 > min)
		range[i++] = min++;
	return (range);
}
