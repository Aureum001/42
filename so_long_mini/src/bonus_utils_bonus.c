/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:57 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 09:33:07 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stdlib.h>
#include <time.h>

void	add_enemy(t_game_bonus *game, int x, int y)
{
	t_enemy	*n;

	n = (t_enemy *)malloc(sizeof(t_enemy));
	if (!n)
		return ;
	n->x = x;
	n->y = y;
	n->direction = rand() % 4;
	n->prev_x = x;
	n->prev_y = y;
	n->next = game->enemies;
	game->enemies = n;
}

void	check_enemy_collision(t_game_bonus *game)
{
	t_enemy	*e;

	e = game->enemies;
	while (e)
	{
		if (e->x == game->base.player_x && e->y == game->base.player_y)
		{
			game->game_over = 1;
			mlx_loop_end(game->base.mlx);
			return ;
		}
		e = e->next;
	}
}

void	free_enemies(t_game_bonus *game)
{
	t_enemy	*e;
	t_enemy	*next;

	e = game->enemies;
	while (e)
	{
		next = e->next;
		free(e);
		e = next;
	}
	game->enemies = NULL;
}
