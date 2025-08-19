/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idle_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:39 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/14 09:32:16 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <time.h>

int	idle_anim_loop(void *param)
{
	static unsigned long	last;
	t_game					*game;
	unsigned long			now;

	last = 0;
	game = (t_game *)param;
	now = (unsigned long)clock();
	if (now - last > (CLOCKS_PER_SEC / 7))
	{
		game->player_frame = (game->player_frame + 1) % 4;
		last = now;
	}
	return (0);
}
