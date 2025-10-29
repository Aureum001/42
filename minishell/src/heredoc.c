/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/29 12:27:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_line(int pipe_fd, const char *delim,
				t_cmd *cmd, int quoted)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (!line || get_heredoc_interrupted())
	{
		if (line)
			free(line);
		return (0);
	}
	if (check_heredoc_delimiter(line, delim))
	{
		free(line);
		return (0);
	}
	write_heredoc_line(pipe_fd, line, cmd, quoted);
	free(line);
	return (1);
}

static void	process_here_doc_input(int pipe_write_fd, const char *delimiter,
				t_cmd *cmd, int quoted)
{
	set_in_heredoc(1);
	while (1)
	{
		if (get_heredoc_interrupted())
			break ;
		write(STDOUT_FILENO, "> ", 2);
		if (!process_heredoc_line(pipe_write_fd, delimiter, cmd, quoted))
			break ;
	}
	set_in_heredoc(0);
}

static int	setup_heredoc_pipe(const char *delimiter, t_cmd *cmd, int quoted)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("minishell: heredoc pipe");
		return (-1);
	}
	process_here_doc_input(pipefd[1], delimiter, cmd, quoted);
	close(pipefd[1]);
	if (get_heredoc_interrupted())
	{
		close(pipefd[0]);
		return (-1);
	}
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
			redir->heredoc_fd = setup_heredoc_pipe(redir->filename,
					cmd, redir->quoted_heredoc);
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
