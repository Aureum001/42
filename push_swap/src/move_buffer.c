/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:28:03 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/23 11:50:18 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	add_move(t_data *data, const char *move)
{
	if (data->buffer.count < MOVE_BUF_SIZE)
		data->buffer.moves[data->buffer.count++] = ft_strdup(move);
}

static int	try_combine_moves(t_data *data, int *i)
{
	char	*move1;
	char	*move2;

	if (*i + 1 >= data->buffer.count)
		return (0);
	move1 = data->buffer.moves[*i];
	move2 = data->buffer.moves[*i + 1];
	if ((!ft_strncmp(move1, "ra", 4) && !ft_strncmp(move2, "rb", 4))
		|| (!ft_strncmp(move1, "rb", 4) && !ft_strncmp(move2, "ra", 4)))
		ft_putstr_fd("rr\n", 1);
	else if ((!ft_strncmp(move1, "rra", 4) && !ft_strncmp(move2, "rrb", 4))
		|| (!ft_strncmp(move1, "rrb", 4) && !ft_strncmp(move2, "rra", 4)))
		ft_putstr_fd("rrr\n", 1);
	else if ((!ft_strncmp(move1, "sa", 4) && !ft_strncmp(move2, "sb", 4))
		|| (!ft_strncmp(move1, "sb", 4) && !ft_strncmp(move2, "sa", 4)))
		ft_putstr_fd("ss\n", 1);
	else
		return (0);
	*i += 2;
	return (1);
}

void	free_buffer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->buffer.count)
	{
		free(data->buffer.moves[i]);
		i++;
	}
	data->buffer.count = 0;
}

void	print_optimized_moves(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->buffer.count)
	{
		if (!try_combine_moves(data, &i))
		{
			ft_putstr_fd(data->buffer.moves[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	free_buffer(data);
}
