/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:25:59 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/19 12:38:14 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	calc_rot(int pos, int size, int *rot, int *dir)
{
	if (pos <= size / 2)
	{
		*rot = pos;
		*dir = 1;
	}
	else
	{
		*rot = size - pos;
		*dir = -1;
	}
}

int	find_max_index_pos(t_stack *stack)
{
	int		max_index;
	int		max_pos;
	int		pos;
	t_stack	*current;

	if (!stack)
		return (0);
	max_index = INT_MIN;
	max_pos = 0;
	pos = 0;
	current = stack;
	while (current)
	{
		if (current->index > max_index)
		{
			max_index = current->index;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

int	get_target_pos_in_b(t_stack *stack_b, int a_index)
{
	t_stack	*current_b;
	int		target_pos;
	long	closest_smaller;
	int		pos;

	current_b = stack_b;
	target_pos = -1;
	closest_smaller = LONG_MIN;
	pos = 0;
	while (current_b)
	{
		if (current_b->index < a_index && current_b->index > closest_smaller)
		{
			closest_smaller = current_b->index;
			target_pos = pos;
		}
		current_b = current_b->next;
		pos++;
	}
	if (closest_smaller == LONG_MIN)
		target_pos = find_max_index_pos(stack_b);
	return (target_pos);
}
