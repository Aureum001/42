/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:41:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 18:33:56 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
			return (free(buffer), free(read_buf), NULL);
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

static void	clean_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char			*buffer;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		clean_buffer(&buffer);
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		clean_buffer(&buffer);
		return (NULL);
	}
	buffer = update_buffer(buffer);
	return (line);
}
