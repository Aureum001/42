/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:31 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/12 11:25:10 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_move_direction(int keycode, int *dx, int *dy)
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

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width)
		return (0);
	if (new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == WALL)
		return (0);
	return (1);
}

/* move logic inlined into perform_move */

static void	handle_collectible_and_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->collectibles--;
		game->map[new_y][new_x] = FLOOR;
	}
	else if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collectibles == 0)
		{
			write(1, "You win!\n", 9);
			cleanup(game);
			exit(0);
		}
	}
}

static void	perform_move(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;
	int	prev_x;
	int	prev_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y))
		return ;
	game->player_frame = (game->player_frame + 1) % 4;
	handle_collectible_and_exit(game, new_x, new_y);
	prev_x = game->player_x;
	prev_y = game->player_y;
	if (game->map[prev_y][prev_x] == PLAYER)
		game->map[prev_y][prev_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	if (game->map[new_y][new_x] != EXIT)
		game->map[new_y][new_x] = PLAYER;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_game(game);
}

int	key_hook(int keycode, void *param)
{
	t_game	*game;
	int		dx;
	int		dy;

	game = (t_game *)param;
	dx = 0;
	dy = 0;
	if (keycode == 65307)
	{
		cleanup(game);
		exit(0);
		return (0);
	}
	get_move_direction(keycode, &dx, &dy);
	if (dx == 0 && dy == 0)
		return (0);
	perform_move(game, dx, dy);
	return (0);
}
