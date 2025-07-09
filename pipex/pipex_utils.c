#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_infile(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("infile");
	return (fd);
}

int	open_outfile(char *file)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("outfile");
	return (fd);
}

int	open_outfile_append(char *file)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_exit("outfile");
	return (fd);
}
