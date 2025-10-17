/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 11:55:46 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_continuation_line(char *initial_input)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line)
	{
		ft_putstr_fd("minishell: unexpected EOF ", 2);
		ft_putstr_fd("while looking for matching quote\n", 2);
		free(initial_input);
		return (NULL);
	}
	tmp = join_with_newline(initial_input, line);
	free(line);
	return (tmp);
}

char	*read_multiline_input(char *initial_input)
{
	char	*tmp;

	while (has_unclosed_quote(initial_input)
		|| has_trailing_pipe(initial_input))
	{
		tmp = handle_continuation_line(initial_input);
		if (!tmp)
			return (NULL);
		initial_input = tmp;
	}
	return (initial_input);
}
