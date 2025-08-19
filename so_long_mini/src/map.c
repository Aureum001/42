/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:10:58 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/18 10:06:46 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_map_cell(t_game *game, int x, int y)
{
	if (game->map[y][x] == PLAYER)
	{
		game->player_x = x;
		game->player_y = y;
		game->player_count++;
	}
	if (game->map[y][x] == COLLECTIBLE)
		game->collectibles++;
	if (game->map[y][x] == EXIT)
		game->exit_count++;
}

void	set_player_and_collectibles(t_game *game)
{
	int	x;
	int	y;

	game->collectibles = 0;
	game->player_count = 0;
	game->exit_count = 0;
	game->player_x = -1;
	game->player_y = -1;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			process_map_cell(game, x, y);
			x++;
		}
		y++;
	}
}

void	flood_fill(char **map, int x, int y, t_ff *st)
{
	char	c;

	if (x < 0 || x >= st->width || y < 0 || y >= st->height)
		return ;
	c = map[y][x];
	if (c == WALL || c == 'V')
		return ;
	if (c == COLLECTIBLE)
		st->collects++;
	if (c == EXIT)
		st->exit_found = 1;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, st);
	flood_fill(map, x - 1, y, st);
	flood_fill(map, x, y + 1, st);
	flood_fill(map, x, y - 1, st);
}
