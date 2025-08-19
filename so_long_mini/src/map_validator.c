/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 11:54:41 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_map_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (y == 0 || y == game->map_height - 1 || x == 0
				|| x == game->map_width - 1)
			{
				if (game->map[y][x] != '1')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_path_and_items(t_game *game)
{
	char	**map_copy;
	t_ff	st;

	if (game->player_x < 0 || game->player_y < 0
		|| game->player_x >= game->map_width
		|| game->player_y >= game->map_height)
		return (0);
	st.collects = 0;
	st.exit_found = 0;
	st.width = game->map_width;
	st.height = game->map_height;
	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, game->player_x, game->player_y, &st);
	free_map_copy(map_copy, game->map_height);
	if (st.collects == game->collectibles && st.exit_found)
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	set_player_and_collectibles(game);
	if (game->player_count != 1 || game->exit_count != 1
		|| game->collectibles < 1)
		return (0);
	if (!is_map_closed(game))
		return (0);
	if (!check_path_and_items(game))
		return (0);
	return (1);
}
