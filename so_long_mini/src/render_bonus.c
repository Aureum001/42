/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:02 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/13 09:50:23 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	erase_prev_tile(t_game_bonus *g, int x, int y)
{
	if (g->base.map[y][x] == WALL)
		mlx_put_image_to_window(g->base.mlx, g->base.win,
			g->base.img_wall, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(g->base.mlx, g->base.win,
			g->base.img_floor, x * TILE_SIZE, y * TILE_SIZE);
	if (g->base.map[y][x] == EXIT)
		mlx_put_image_to_window(g->base.mlx, g->base.win,
			g->base.img_exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (g->base.map[y][x] == COLLECTIBLE)
		mlx_put_image_to_window(g->base.mlx, g->base.win,
			g->base.img_collectible, x * TILE_SIZE, y * TILE_SIZE);
}

static void	draw_enemies(t_game_bonus *g)
{
	t_enemy	*e;
	int		frame;

	e = g->enemies;
	while (e)
	{
		frame = (e->x + e->y) % 6;
		if (g->static_drawn && (e->prev_x != e->x || e->prev_y != e->y))
			erase_prev_tile(g, e->prev_x, e->prev_y);
		mlx_put_image_to_window(g->base.mlx, g->base.win,
			g->img_enemy[frame], e->x * TILE_SIZE, e->y * TILE_SIZE);
		e = e->next;
	}
}

static void	draw_player_bonus(t_game_bonus *g)
{
	void	*img;

	if (g->static_drawn && (g->prev_player_x != g->base.player_x
			|| g->prev_player_y != g->base.player_y))
		erase_prev_tile(g, g->prev_player_x, g->prev_player_y);
	img = g->base.img_idle[g->base.player_frame];
	mlx_put_image_to_window(g->base.mlx, g->base.win, img,
		g->base.player_x * TILE_SIZE, g->base.player_y * TILE_SIZE);
}

void	render_game_bonus(t_game_bonus *game)
{
	if (!game->static_drawn)
	{
		render_game(&game->base);
		game->static_drawn = 1;
	}
	draw_enemies(game);
	draw_player_bonus(game);
	if (game->img_hud)
		mlx_put_image_to_window(game->base.mlx, game->base.win,
			game->img_hud, 0, 0);
	render_moves_on_screen(game);
}
