/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 10:02:08 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_here_doc_input(int pipe_write_fd, const char *delimiter,
				t_cmd *cmd)
{
	char	*line;
	char	*expanded_line;
	size_t	line_len;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line_len = ft_strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_variables(line, cmd->envp, cmd->last_status);
		ft_putendl_fd(expanded_line, pipe_write_fd);
		free(line);
		free(expanded_line);
	}
}

static int	setup_heredoc_pipe(const char *delimiter, t_cmd *cmd)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("minishell: heredoc pipe");
		return (-1);
	}
	process_here_doc_input(pipefd[1], delimiter, cmd);
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	process_cmd_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			redir->heredoc_fd = setup_heredoc_pipe(redir->filename, cmd);
			if (redir->heredoc_fd < 0)
				return ;
		}
		redir = redir->next;
	}
}

void	process_all_heredocs(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		process_cmd_heredocs(current);
		current = current->next;
	}
}
