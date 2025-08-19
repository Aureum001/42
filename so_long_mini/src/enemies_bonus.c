/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/12 11:33:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_enemy_at(t_game_bonus *game, int x, int y)
{
	t_enemy	*p;

	p = game->enemies;
	while (p)
	{
		if (p->x == x && p->y == y)
			return (1);
		p = p->next;
	}
	return (0);
}

static void	step_from_dir(t_enemy *e, int dir, int *nx, int *ny)
{
	*nx = e->x;
	*ny = e->y;
	if (dir == 0)
		(*ny)--;
	else if (dir == 1)
		(*ny)++;
	else if (dir == 2)
		(*nx)--;
	else if (dir == 3)
		(*nx)++;
}

static int	can_move_to(t_game_bonus *g, int x, int y)
{
	if (x < 0 || x >= g->base.map_width)
		return (0);
	if (y < 0 || y >= g->base.map_height)
		return (0);
	if (g->base.map[y][x] == WALL || g->base.map[y][x] == EXIT)
		return (0);
	if (is_enemy_at(g, x, y))
		return (0);
	return (1);
}

void	update_enemies(t_game_bonus *game)
{
	t_enemy	*e;
	int		dir;
	int		nx;
	int		ny;

	e = game->enemies;
	while (e)
	{
		dir = rand() % 4;
		step_from_dir(e, dir, &nx, &ny);
		if (can_move_to(game, nx, ny))
		{
			e->prev_x = e->x;
			e->prev_y = e->y;
			e->x = nx;
			e->y = ny;
		}
		e = e->next;
	}
}
