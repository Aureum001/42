/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:01 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 11:02:12 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	handle_here_doc(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	handle_redirections(t_cmd *cmd, int *in_fd, int *out_fd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
			*in_fd = open(redir->filename, O_RDONLY);
		else if (redir->type == TOKEN_REDIRECT_OUT)
			*out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_REDIRECT_APPEND)
			*out_fd = open(redir->filename, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (redir->type == TOKEN_HEREDOC)
			*in_fd = handle_here_doc(redir->filename);
		if (*in_fd < 0 || *out_fd < 0)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	free(path);
	perror("minishell");
	exit(EXIT_FAILURE);
}
