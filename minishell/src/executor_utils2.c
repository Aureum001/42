/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:08 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/06 10:08:15 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_aux(t_cmd *cmd, char **envp)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd))
	{
		status = execute_builtin(cmd);
		exit(status);
	}
	else
		execute_command(cmd, envp);
}

void	child_process(t_cmd *cmd, char **envp, int in_fd, int pipefd[2])
{
	int	out_fd;

	out_fd = STDOUT_FILENO;
	if (cmd->next)
	{
		close(pipefd[0]);
		out_fd = pipefd[1];
	}
	handle_redirections(cmd, &in_fd, &out_fd);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	child_process_aux(cmd, envp);
}
