/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:10:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 11:46:13 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_game_state(t_game *g)
{
	g->moves = 0;
	g->player_frame = 0;
}

static void	setup_window_and_images_mand(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		error_exit("MLX init failed");
	g->win = mlx_new_window(g->mlx, g->map_width * TILE_SIZE,
			g->map_height * TILE_SIZE, "so_long");
	if (!g->win)
		error_exit("Window creation failed");
	mlx_set_font(g->mlx, g->win, "10x20");
	load_images(g);
	mlx_hook(g->win, 17, 0, cleanup_and_exit, g);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game_state(&game);
	if (argc != 2)
		error_exit("Usage: ./so_long <map.ber>");
	if (!load_map(&game, argv[1]))
		error_exit("Failed to load map");
	if (!validate_map(&game))
	{
		free_map(game.map);
		error_exit("Invalid map");
	}
	setup_window_and_images_mand(&game);
	render_game(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, idle_anim_loop, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
