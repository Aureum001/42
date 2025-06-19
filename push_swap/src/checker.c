/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:52:06 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/13 13:18:15 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	apply_swap_commands(char *command, t_data *data)
{
	if (ft_strncmp(command, "sa", 2) == 0)
		sa(data, 0);
	else if (ft_strncmp(command, "sb", 2) == 0)
		sb(data, 0);
	else if (ft_strncmp(command, "ss", 2) == 0)
		ss(data, 0);
}

static void	apply_push_commands(char *command, t_data *data)
{
	if (ft_strncmp(command, "pa", 2) == 0)
		pa(data, 0);
	else if (ft_strncmp(command, "pb", 2) == 0)
		pb(data, 0);
}

static void	apply_rotate_commands(char *command, t_data *data)
{
	if (ft_strncmp(command, "ra", 2) == 0)
		ra(data, 0);
	else if (ft_strncmp(command, "rb", 2) == 0)
		rb(data, 0);
	else if (ft_strncmp(command, "rr", 2) == 0)
		rr(data, 0);
}

static void	apply_reverse_rotate_commands(char *command, t_data *data)
{
	if (ft_strncmp(command, "rra", 3) == 0)
		rra(data, 0);
	else if (ft_strncmp(command, "rrb", 3) == 0)
		rrb(data, 0);
	else if (ft_strncmp(command, "rrr", 3) == 0)
		rrr(data, 0);
}

int	apply_command(char *command, t_data *data)
{
	if (!command)
		return (0);
	if (ft_strncmp(command, "sa", 2) == 0 || ft_strncmp(command, "sb", 2) == 0
		|| ft_strncmp(command, "ss", 2) == 0)
		apply_swap_commands(command, data);
	else if (ft_strncmp(command, "pa", 2) == 0
		|| ft_strncmp(command, "pb", 2) == 0)
		apply_push_commands(command, data);
	else if (ft_strncmp(command, "ra", 2) == 0
		|| ft_strncmp(command, "rb", 2) == 0 || ft_strncmp(command, "rr", 2) == 0)
		apply_rotate_commands(command, data);
	else if (ft_strncmp(command, "rra", 3) == 0
		|| ft_strncmp(command, "rrb", 3) == 0 || ft_strncmp(command, "rrr", 3) == 0)
		apply_reverse_rotate_commands(command, data);
	else
		return (0);
	return (1);
}
