/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:41:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/24 12:05:13 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*process_reading(int fd, char *buffer, char *read_buf)
{
	char	*temp;
	int		bytes_read;

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
		temp = ft_strjoin(buffer, read_buf);
		if (!temp)
		{
			free(buffer);
			free(read_buf);
			return (NULL);
		}
		buffer = temp;
	}
	free(read_buf);
	return (buffer);
}

static char	*read_file(int fd, char *buffer)
{
	char	*read_buf;

	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
	{
		free(buffer);
		return (NULL);
	}
	return (process_reading(fd, buffer, read_buf));
}

static char	*extract_line(char *buffer)
{
	char	*line;
	char	*ptr;

	if (!buffer || !buffer[0])
		return (NULL);
	ptr = buffer;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	line = malloc(ptr - buffer + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, ptr - buffer + 1);
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

char	*get_next_line(int fd)
{
	static char		*buffers[1024];
	char			*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	if (!line)
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	buffers[fd] = update_buffer(buffers[fd]);
	return (line);
}
