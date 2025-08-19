/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:45:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/18 10:06:30 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	process_cell_for_validation(t_game_bonus *g, int x, int y)
{
	if (g->base.map[y][x] == PLAYER)
	{
		g->base.player_x = x;
		g->base.player_y = y;
		g->base.player_count++;
	}
	if (g->base.map[y][x] == COLLECTIBLE)
		g->base.collectibles++;
	if (g->base.map[y][x] == EXIT)
		g->base.exit_count++;
}

void	scan_map_for_validation(t_game_bonus *g)
{
	int	x;
	int	y;

	g->base.collectibles = 0;
	g->base.player_count = 0;
	g->base.exit_count = 0;
	g->base.player_x = -1;
	g->base.player_y = -1;
	y = 0;
	while (y < g->base.map_height)
	{
		x = 0;
		while (x < g->base.map_width)
		{
			process_cell_for_validation(g, x, y);
			x++;
		}
		y++;
	}
}

static void	process_bonus_cell(t_game_bonus *g, int x, int y)
{
	if (g->base.map[y][x] == 'X')
	{
		add_enemy(g, x, y);
		g->base.map[y][x] = '0';
	}
}

void	parse_map_bonus(t_game_bonus *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->base.map_height)
	{
		x = 0;
		while (x < g->base.map_width)
		{
			process_bonus_cell(g, x, y);
			x++;
		}
		y++;
	}
}
