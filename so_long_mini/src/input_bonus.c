/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:35 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 09:48:44 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	get_move_dir(int keycode, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (keycode == 119 || keycode == 65362)
		*dy = -1;
	else if (keycode == 115 || keycode == 65364)
		*dy = 1;
	else if (keycode == 97 || keycode == 65361)
		*dx = -1;
	else if (keycode == 100 || keycode == 65363)
		*dx = 1;
}

static int	is_oob_or_wall(t_game_bonus *g, int nx, int ny)
{
	if (nx < 0 || nx >= g->base.map_width)
		return (1);
	if (ny < 0 || ny >= g->base.map_height)
		return (1);
	if (g->base.map[ny][nx] == WALL)
		return (1);
	return (0);
}

static void	apply_and_commit_move(t_game_bonus *g, int nx, int ny, char tile)
{
	if (tile == COLLECTIBLE)
		g->base.collectibles--;
	else if (tile == EXIT && g->base.collectibles == 0)
	{
		write(1, "You win!\n", 9);
		free_enemies(g);
		cleanup(&g->base);
		exit(0);
	}
	g->prev_player_x = g->base.player_x;
	g->prev_player_y = g->base.player_y;
	if (g->base.map[g->prev_player_y][g->prev_player_x] == PLAYER)
		g->base.map[g->prev_player_y][g->prev_player_x] = FLOOR;
	g->base.player_x = nx;
	g->base.player_y = ny;
	if (tile == COLLECTIBLE)
		g->base.map[ny][nx] = FLOOR;
	if (tile != EXIT)
		g->base.map[ny][nx] = PLAYER;
}

static int	move_player_bonus(t_game_bonus *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;

	nx = g->base.player_x + dx;
	ny = g->base.player_y + dy;
	if (is_oob_or_wall(g, nx, ny))
		return (0);
	tile = g->base.map[ny][nx];
	apply_and_commit_move(g, nx, ny, tile);
	return (1);
}

int	key_hook_bonus(int keycode, void *param)
{
	t_game_bonus	*g;
	int				dx;
	int				dy;

	g = (t_game_bonus *)param;
	if (keycode == 65307)
	{
		free_enemies(g);
		cleanup(&g->base);
		exit(0);
	}
	get_move_dir(keycode, &dx, &dy);
	if (dx == 0 && dy == 0)
		return (0);
	if (!move_player_bonus(g, dx, dy))
		return (0);
	g->base.moves++;
	g->base.player_frame = (g->base.player_frame + 1) % 4;
	render_game_bonus(g);
	return (0);
}
