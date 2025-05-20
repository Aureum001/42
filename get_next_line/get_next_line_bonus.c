/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:41:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 19:32:47 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *buffer)
{
	char	*read_buf;
	int		bytes_read;

	if (!buffer)
		buffer = ft_strdup("");
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(read_buf);
			return (NULL);
		}
		read_buf[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, read_buf);
		if (!buffer)
			break ;
	}
	free(read_buf);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*newline_ptr;

	if (!buffer)
		return (NULL);
	newline_ptr = ft_strchr(buffer, '\n');
	if (!newline_ptr)
	{
		free(buffer);
		return (NULL);
	}
	newline_ptr++;
	new_buffer = malloc(ft_strlen(buffer) - (newline_ptr - buffer) + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(new_buffer, newline_ptr, ft_strlen(newline_ptr) + 1);
	free(buffer);
	return (new_buffer);
}

static void	clean_buffer_fd(char **buffers, int fd)
{
	if (fd >= 0 && fd < FD_MAX && buffers[fd])
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char		*buffers[FD_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		clean_buffer_fd(buffers, fd);
		return (NULL);
	}
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	if (!line)
	{
		clean_buffer_fd(buffers, fd);
		return (NULL);
	}
	buffers[fd] = update_buffer(buffers[fd]);
	return (line);
}
