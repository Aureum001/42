/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/27 09:38:54 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_executing = 0;

void	set_executing(int value)
{
	g_executing = value;
}

int	get_executing(void)
{
	return (g_executing);
}
