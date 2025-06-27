/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/23 09:45:22 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = (*stack)->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_data *data, int print)
{
	swap(&data->stack_a);
	if (print)
		add_move(data, "sa");
}

void	sb(t_data *data, int print)
{
	swap(&data->stack_b);
	if (print)
		add_move(data, "sb");
}

void	ss(t_data *data, int print)
{
	swap(&data->stack_a);
	swap(&data->stack_b);
	if (print)
		add_move(data, "ss");
}
