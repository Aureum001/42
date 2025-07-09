#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

static int	handle_here_doc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		error_exit("here_doc pipe");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) && line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	launch_middle_children(int argc, char **argv, char **envp, t_pipex *px)
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
		{
			close(px->pipefd[0]);
			child_process(argv[i], px->prev_fd, px->pipefd[1], envp);
		}
		close(px->pipefd[1]);
		if (px->prev_fd != px->infile_fd)
			close(px->prev_fd);
		px->prev_fd = px->pipefd[0];
		i++;
	}
}

static void	pipex(int argc, char **argv, char **envp)
{
	t_pipex px;

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
