/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/13 13:48:58 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_atol_ps(const char *str, int *error_flag)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	*error_flag = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		*error_flag = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		*error_flag = 1;
	return (result * sign);
}

void	add_node_to_stack_end(t_stack **stack, int value)
{
	t_stack	*new_node;
	t_stack	*current;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return ; // Proper error handling would involve freeing existing stack
	new_node->value = value;
	new_node->index = 0; // Index will be assigned later
	new_node->next = NULL;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	current = *stack;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
