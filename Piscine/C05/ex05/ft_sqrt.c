/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:14:51 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/10 17:51:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	left;
	int	right;
	int	mid;
	int	square;

	left = 0;
	right = nb;
	if (nb < 0)
		return (-1);
	while (left <= right)
	{
		mid = (left + right) / 2;
		square = mid * mid;
		if (square == nb)
			return (mid);
		else if (square < nb)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (0);
}
