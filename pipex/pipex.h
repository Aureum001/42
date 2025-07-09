#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

typedef struct s_pipex
{
	int infile_fd;
	int outfile_fd;
	int prev_fd;
	int pipefd[2];
	pid_t pid;
	int here_doc;
} t_pipex;

void	error_exit(const char *msg);
int	open_infile(char *file);
int	open_outfile(char *file);
int	open_outfile_append(char *file);
char	**ft_split(char const *s, char c);
char	*find_cmd_path(char *cmd, char **envp);

#endif