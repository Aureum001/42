/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:48:11 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/07 10:19:54 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>

static int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_status;
	pid_t	pid;

	exit_status = 0;
	pid = waitpid(last_pid, &status, 0);
	if (pid == last_pid)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (wait(NULL) > 0)
		;
	return (exit_status);
}

int	executor(t_cmd *cmd_list)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*current_cmd;

	in_fd = STDIN_FILENO;
	pid = -1;
	current_cmd = cmd_list;
	while (current_cmd)
	{
		if (current_cmd->next)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
			child_process(current_cmd, in_fd, pipefd);
		if (pid < 0)
		{
			perror("fork");
			break ;
		}
		manage_parent_fds(&in_fd, pipefd, current_cmd);
		current_cmd = current_cmd->next;
	}
	return (wait_for_children(pid));
}
