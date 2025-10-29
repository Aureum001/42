/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:45:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 10:37:48 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_interrupted(int value)
{
	if (value)
		set_status_bit(1, 1);
	else
		set_status_bit(1, 0);
}

int	get_heredoc_interrupted(void)
{
	return (get_status_bit(1));
}

void	set_in_heredoc(int value)
{
	if (value)
		set_status_bit(2, 1);
	else
		set_status_bit(2, 0);
}

int	get_in_heredoc(void)
{
	return (get_status_bit(2));
}
