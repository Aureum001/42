/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:10:54 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 11:36:30 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

static int	check_line_width(const char *line, int *width)
{
	int	w;

	w = ft_strlen(line);
	if (w > 0 && line[w - 1] == '\n')
		w--;
	if (*width == -1)
		*width = w;
	if (w != *width)
		return (0);
	return (1);
}

static int	count_lines_and_width(const char *filename, int *width, int *height)
{
	int		fd;
	char	*line;

	*height = 0;
	*width = -1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!check_line_width(line, width))
		{
			free(line);
			gnl_drain(fd);
			return (close(fd), 0);
		}
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), *height > 0 && *width > 0);
}

static int	fill_map_row(char **map, int i, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	map[i] = ft_strdup(line);
	free(line);
	if (!map[i])
		return (0);
	return (1);
}

static int	read_map_rows(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (i < game->map_height && line)
	{
		if (!fill_map_row(game->map, i, line))
		{
			while (--i >= 0)
				free(game->map[i]);
			free(game->map);
			close(fd);
			return (0);
		}
		i++;
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

int	load_map(t_game *game, const char *filename)
{
	int	fd;

	if (!count_lines_and_width(filename, &game->map_width, &game->map_height))
		return (0);
	game->map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map);
		return (0);
	}
	return (read_map_rows(game, fd));
}
