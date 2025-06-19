/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/12 11:03:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push(t_stack **dest, t_stack **src)
{
	t_stack	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

void	pa(t_data *data, int print)
{
	push(&data->stack_a, &data->stack_b);
	data->size_a++;
	data->size_b--;
	if (print)
		ft_putstr_fd("pa\n", 1);
}

void	pb(t_data *data, int print)
{
	push(&data->stack_b, &data->stack_a);
	data->size_b++;
	data->size_a--;
	if (print)
		ft_putstr_fd("pb\n", 1);
}

static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = stack_last(*stack);
	*stack = first->next;
	first->next = NULL;
	last->next = first;
}

void	ra(t_data *data, int print)
{
	rotate(&data->stack_a);
	if (print)
		ft_putstr_fd("ra\n", 1);
}
