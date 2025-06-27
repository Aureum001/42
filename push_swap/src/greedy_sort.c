/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:25:43 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/19 12:43:43 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	calculate_cost(t_move_plan *plan)
{
	if (plan->a_dir == plan->b_dir)
	{
		if (plan->a_rot > plan->b_rot)
			plan->cost = plan->a_rot;
		else
			plan->cost = plan->b_rot;
	}
	else
		plan->cost = plan->a_rot + plan->b_rot;
}

static void	find_best_move(t_data *data, t_move_plan *best_plan)
{
	t_stack		*curr_a;
	t_move_plan	current_plan;
	int			pos;
	int			target_pos_b;

	curr_a = data->stack_a;
	pos = 0;
	best_plan->cost = INT_MAX;
	while (curr_a)
	{
		calc_rot(pos, data->size_a, &current_plan.a_rot, &current_plan.a_dir);
		target_pos_b = get_target_pos_in_b(data->stack_b, curr_a->index);
		calc_rot(target_pos_b, data->size_b, &current_plan.b_rot,
			&current_plan.b_dir);
		calculate_cost(&current_plan);
		if (current_plan.cost < best_plan->cost)
			*best_plan = current_plan;
		curr_a = curr_a->next;
		pos++;
	}
}

static void	execute_move(t_data *data, t_move_plan *plan)
{
	int	a_rot;
	int	b_rot;

	a_rot = plan->a_rot;
	b_rot = plan->b_rot;
	while (a_rot > 0 && b_rot > 0 && plan->a_dir == plan->b_dir)
	{
		if (plan->a_dir == 1)
			rr(data, 1);
		else
			rrr(data, 1);
		a_rot--;
		b_rot--;
	}
	while (a_rot-- > 0)
		if (plan->a_dir == 1)
			ra(data, 1);
	else
		rra(data, 1);
	while (b_rot-- > 0)
		if (plan->b_dir == 1)
			rb(data, 1);
	else
		rrb(data, 1);
	pb(data, 1);
}

static void	finalize_stack_b(t_data *data)
{
	int	max_pos;
	int	r;

	max_pos = find_max_index_pos(data->stack_b);
	if (max_pos <= data->size_b / 2)
	{
		while (max_pos-- > 0)
			rb(data, 1);
	}
	else
	{
		r = data->size_b - max_pos;
		while (r-- > 0)
			rrb(data, 1);
	}
}

void	greedy_sort(t_data *data)
{
	t_move_plan	best_plan;

	assign_index(data);
	if (data->size_a > 2)
		pb(data, 1);
	if (data->size_a > 2)
		pb(data, 1);
	while (data->size_a > 0)
	{
		find_best_move(data, &best_plan);
		execute_move(data, &best_plan);
	}
	finalize_stack_b(data);
	while (data->size_b > 0)
		pa(data, 1);
}
