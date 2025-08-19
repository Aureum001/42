/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:12:01 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/12 11:50:58 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ensure types and prototypes are visible before use
#include "so_long_bonus.h"

static void	*load_image_or_exit(void *mlx, char *path, char *err_msg)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		error_exit(err_msg);
	return (img);
}

void	load_images(t_game *game)
{
	game->img_wall = load_image_or_exit(game->mlx,
			"assets/gwall.xpm", "Failed to load wall texture");
	game->img_floor = load_image_or_exit(game->mlx,
			"assets/floor.xpm", "Failed to load floor texture");
	game->img_exit = load_image_or_exit(game->mlx,
			"assets/exit.xpm", "Failed to load exit texture");
	game->img_collectible = load_image_or_exit(game->mlx,
			"assets/coin.xpm", "Failed to load coin texture");
	game->img_idle[0] = load_image_or_exit(game->mlx,
			"assets/player/idle/idle01.xpm", "Failed to load idle frame 1");
	game->img_idle[1] = load_image_or_exit(game->mlx,
			"assets/player/idle/idle02.xpm", "Failed to load idle frame 2");
	game->img_idle[2] = load_image_or_exit(game->mlx,
			"assets/player/idle/idle03.xpm", "Failed to load idle frame 3");
	game->img_idle[3] = load_image_or_exit(game->mlx,
			"assets/player/idle/idle04.xpm", "Failed to load idle frame 4");
	if (!game->img_idle[0] || !game->img_idle[1]
		|| !game->img_idle[2] || !game->img_idle[3]
		|| !game->img_wall || !game->img_floor
		|| !game->img_exit || !game->img_collectible)
		error_exit("Failed to load or display one or more images");
}

void	load_images_bonus(t_game_bonus *game)
{
	load_images(&game->base);
	game->img_enemy[0] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar000.xpm", "Failed to load enemy frame 0");
	game->img_enemy[1] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar001.xpm", "Failed to load enemy frame 1");
	game->img_enemy[2] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar002.xpm", "Failed to load enemy frame 2");
	game->img_enemy[3] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar003.xpm", "Failed to load enemy frame 3");
	game->img_enemy[4] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar004.xpm", "Failed to load enemy frame 4");
	game->img_enemy[5] = load_image_or_exit(game->base.mlx,
			"assets/enemy/boar005.xpm", "Failed to load enemy frame 5");
}
