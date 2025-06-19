/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:56:17 by ancanale         ###   ########.fr       */
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
		ft_putstr_fd("sa\n", 1);
}

void	sb(t_data *data, int print)
{
	swap(&data->stack_b);
	if (print)
		ft_putstr_fd("sb\n", 1);
}

void	ss(t_data *data, int print)
{
	swap(&data->stack_a);
	swap(&data->stack_b);
	if (print)
		ft_putstr_fd("ss\n", 1);
}
