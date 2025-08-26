/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:42:06 by ancanale          #+#    #+#             */
/*   Updated: 2025/07/30 09:55:25 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	handle_here_doc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	int		written;

	if (pipe(pipefd) == -1)
		error_exit("here_doc pipe");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter,
				ft_strlen(delimiter)) && line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		written = write(pipefd[1], line, ft_strlen(line));
		if (written < 0)
			error_exit("write");
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
