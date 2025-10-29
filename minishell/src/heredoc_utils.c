/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:35:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 12:27:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc_line(int pipe_fd, char *line, t_cmd *cmd, int quoted)
{
	char	*expanded_line;

	if (quoted)
		ft_putendl_fd(line, pipe_fd);
	else
	{
		expanded_line = expand_variables(line, cmd->envp, cmd->last_status);
		ft_putendl_fd(expanded_line, pipe_fd);
		free(expanded_line);
	}
}

int	check_heredoc_delimiter(char *line, const char *delim)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		return (1);
	return (0);
}
