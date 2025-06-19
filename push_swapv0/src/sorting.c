/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/12 11:02:38 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	find_min_index(t_stack *stack)
{
	int		min_index;
	int		current_index;
	int		min_value;
	t_stack	*current;

	if (!stack)
		return (-1);
	min_value = stack->value;
	min_index = 0;
	current_index = 0;
	current = stack;
	while (current)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_index = current_index;
		}
		current = current->next;
		current_index++;
	}
	return (min_index);
}

static void	rotate_min_to_top(t_data *data, int min_index, int size)
{
	if (min_index <= size / 2)
	{
		while (min_index-- > 0)
			ra(data, 1);
	}
	else
	{
		while (min_index++ < size)
			rra(data, 1);
	}
}

static void	move_min_to_b(t_data *data)
{
	int	min_index;
	int	size;

	size = data->size_a;
	min_index = find_min_index(data->stack_a);
	rotate_min_to_top(data, min_index, size);
	pb(data, 1);
}

void	sort_three(t_data *data)
{
	int	a;
	int	b;
	int	c;

	if (data->size_a != 3)
		return ;
	a = data->stack_a->value;
	b = data->stack_a->next->value;
	c = data->stack_a->next->next->value;
	if (a > b && b < c && a < c)
		sa(data, 1);
	else if (a > b && b > c)
	{
		sa(data, 1);
		rra(data, 1);
	}
	else if (a > b && b < c && a > c)
		ra(data, 1);
	else if (a < b && b > c && a < c)
	{
		sa(data, 1);
		ra(data, 1);
	}
	else if (a < b && b > c && a > c)
		rra(data, 1);
}

void	sort_five(t_data *data)
{
	if (is_sorted(data->stack_a))
		return ;
	while (data->size_a > 3)
		move_min_to_b(data);
	sort_three(data);
	while (data->size_b > 0)
		pa(data, 1);
}
