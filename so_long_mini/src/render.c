/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:07 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/12 11:11:08 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_cell(t_game *game, int x, int y)
{
	if (game->map[y][x] == WALL)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map[y][x] == EXIT)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == COLLECTIBLE)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
}

static void	draw_player(t_game *game)
{
	void	*player_img;

	player_img = game->img_idle[game->player_frame];
	mlx_put_image_to_window(game->mlx, game->win, player_img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_cell(game, x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
}
