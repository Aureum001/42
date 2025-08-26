/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:20:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/07/30 09:52:19 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"
#include <unistd.h>
#include <stdlib.h>

void	child_process(char *cmd, int in_fd, int out_fd, char **envp)
{
	char	**args;
	char	*path;

	if (dup2(in_fd, 0) < 0)
		error_exit("dup2 in_fd");
	if (dup2(out_fd, 1) < 0)
		error_exit("dup2 out_fd");
	args = ft_split(cmd, ' ');
	path = find_cmd_path(args[0], envp);
	if (!path)
		error_exit("command not found");
	execve(path, args, envp);
	error_exit("execve");
}

static void	middle_child(t_pipex *px, char *cmd, char **envp)
{
	close(px->pipefd[0]);
	child_process(cmd, px->prev_fd, px->pipefd[1], envp);
}

static void	launch_middle_children(int argc, char **argv,
						char **envp, t_pipex *px)
{
	int		i;

	if (px->here_doc)
		i = 3;
	else
		i = 2;
	px->prev_fd = px->infile_fd;
	while (i < argc - 2)
	{
		if (pipe(px->pipefd) == -1)
		{
			close(px->prev_fd);
			error_exit("pipe");
		}
		px->pid = fork();
		if (px->pid < 0)
			error_exit("fork");
		if (px->pid == 0)
			middle_child(px, argv[i], envp);
		close(px->pipefd[1]);
		if (px->prev_fd != px->infile_fd)
			close(px->prev_fd);
		px->prev_fd = px->pipefd[0];
		i++;
	}
}

static void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;

	px.here_doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		px.here_doc = 1;
	if (px.here_doc)
	{
		px.infile_fd = handle_here_doc(argv[2]);
		px.outfile_fd = open_outfile_append(argv[argc - 1]);
	}
	else
	{
		px.infile_fd = open_infile(argv[1]);
		px.outfile_fd = open_outfile(argv[argc - 1]);
	}
	launch_middle_children(argc, argv, envp, &px);
	px.pid = fork();
	if (px.pid < 0)
		error_exit("fork");
	if (px.pid == 0)
		child_process(argv[argc - 2], px.prev_fd, px.outfile_fd, envp);
	close(px.prev_fd);
	close(px.outfile_fd);
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 ... cmdN outfile\n", 44);
		write(2, "   or: ./pipex here_doc LIMITER cmd1 ... cmdN outfile\n", 56);
		return (1);
	}
	pipex(argc, argv, envp);
	return (0);
}
