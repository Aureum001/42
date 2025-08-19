/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:27:33 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/14 10:27:45 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

int	cleanup_and_exit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup(game);
	exit(0);
	return (0);
}
