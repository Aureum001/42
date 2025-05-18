/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:41:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 18:27:05 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *buffer)
{
	char	*read_buf;
	int		bytes_read;
	char	*temp;

	if (!buffer)
		buffer = ft_strdup("");
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (buffer = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(read_buf), NULL);
		read_buf[bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, read_buf);
		free(temp);
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
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	new_buffer = malloc(ft_strlen(buffer) - i + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static t_fd_list	*get_or_create_node(int fd, t_fd_list **fd_list)
{
	t_fd_list	*node;

	node = find_fd_node(fd_list, fd);
	if (!node)
	{
		node = create_fd_node(fd);
		if (!node)
			return (NULL);
		node->next = *fd_list;
		*fd_list = node;
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0)
			return (free_fd_node(&fd_list, fd), NULL);
	}
	node = get_or_create_node(fd, &fd_list);
	if (!node)
		return (NULL);
	node->buffer = read_file(node->fd, node->buffer);
	if (!node->buffer)
		return (free_fd_node(&fd_list, fd), NULL);
	line = extract_line(node->buffer);
	if (!line)
	{
		free(node->buffer);
		return (node->buffer = NULL, free_fd_node(&fd_list, fd), NULL);
	}
	node->buffer = update_buffer(node->buffer);
	if (!node->buffer)
		free_fd_node(&fd_list, fd);
	return (line);
}
