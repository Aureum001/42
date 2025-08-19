/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:27 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 09:50:06 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stdlib.h>
#include <time.h>

static void	setup_window_and_images(t_game_bonus *g)
{
	int			width;
	int			height;
	t_hudspec	spec;

	width = g->base.map_width * TILE_SIZE;
	height = g->base.map_height * TILE_SIZE;
	g->base.mlx = mlx_init();
	if (!g->base.mlx)
		error_exit("MLX init failed");
	g->base.win = mlx_new_window(g->base.mlx, width, height, "so_long_bonus");
	if (!g->base.win)
		error_exit("Window creation failed");
	mlx_set_font(g->base.mlx, g->base.win, "10x20");
	spec.w = width;
	spec.h = 24;
	spec.color = 0x202020;
	create_hud_image(g, spec);
	load_images_bonus(g);
	mlx_hook(g->base.win, 17, 0, cleanup_and_exit_bonus, g);
}

static void	init_bonus_defaults(t_game_bonus *g)
{
	g->enemies = NULL;
	g->game_over = 0;
	g->enemy_tick = 0;
	g->enemy_speed = 24;
	g->enemy_last_ms = 0;
	g->enemy_interval_ms = 500;
	g->static_drawn = 0;
	g->base.moves = 0;
	g->base.player_frame = 0;
	g->prev_player_x = 0;
	g->prev_player_y = 0;
}

int	enemy_update_hook(void *param)
{
	t_game_bonus	*g;

	g = (t_game_bonus *)param;
	if (g->game_over)
		return (0);
	idle_anim_loop(&g->base);
	if (g->enemy_last_ms == 0)
		g->enemy_last_ms = current_time_ms();
	if (current_time_ms() - g->enemy_last_ms >= g->enemy_interval_ms)
	{
		g->enemy_last_ms = current_time_ms();
		update_enemies(g);
	}
	check_enemy_collision(g);
	render_game_bonus(g);
	return (0);
}

static void	run_bonus_loop(t_game_bonus *g)
{
	mlx_key_hook(g->base.win, key_hook_bonus, g);
	mlx_loop_hook(g->base.mlx, enemy_update_hook, g);
	mlx_loop(g->base.mlx);
}

int	main(int argc, char **argv)
{
	t_game_bonus	game;

	if (argc != 2)
		error_exit("Usage: ./so_long_bonus <map.ber>");
	srand(time(NULL));
	init_bonus_defaults(&game);
	if (!load_map(&game.base, argv[1]))
		error_exit("Failed to load map");
	scan_map_for_validation(&game);
	if (!validate_map(&game.base))
		error_exit("Invalid map");
	parse_map_bonus(&game);
	setup_window_and_images(&game);
	render_game_bonus(&game);
	run_bonus_loop(&game);
	free_enemies(&game);
	cleanup(&game.base);
	return (0);
}
