/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:23:09 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/23 12:37:25 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/push_swap_bonus.h"

static void	remove_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
}

static int	apply_command(char *command, t_data *data)
{
	if (ft_strncmp(command, "sa", 3) == 0)
		sa(data, 0);
	else if (ft_strncmp(command, "sb", 3) == 0)
		sb(data, 0);
	else if (ft_strncmp(command, "ss", 3) == 0)
		ss(data, 0);
	else if (ft_strncmp(command, "pa", 3) == 0)
		pa(data, 0);
	else if (ft_strncmp(command, "pb", 3) == 0)
		pb(data, 0);
	else if (ft_strncmp(command, "ra", 3) == 0)
		ra(data, 0);
	else if (ft_strncmp(command, "rb", 3) == 0)
		rb(data, 0);
	else if (ft_strncmp(command, "rr", 3) == 0)
		rr(data, 0);
	else if (ft_strncmp(command, "rra", 4) == 0)
		rra(data, 0);
	else if (ft_strncmp(command, "rrb", 4) == 0)
		rrb(data, 0);
	else if (ft_strncmp(command, "rrr", 4) == 0)
		rrr(data, 0);
	else
		return (0);
	return (1);
}

void	process_commands(t_data *data)
{
	char	*line;
	int		error_found;

	error_found = 0;
	line = get_next_line(0);
	while (line != NULL)
	{
		remove_newline(line);
		if (!error_found && !apply_command(line, data))
			error_found = 1;
		free(line);
		line = get_next_line(0);
	}
	if (error_found)
		error_exit(data);
}
