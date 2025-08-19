/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:24:19 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 09:41:52 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stdlib.h>

int	cleanup_and_exit_bonus(void *param)
{
	t_game_bonus	*game;

	game = (t_game_bonus *)param;
	free_enemies(game);
	cleanup(&game->base);
	exit(0);
	return (0);
}
