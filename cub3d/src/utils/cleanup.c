#include "cub3d.h"
#include <stdlib.h>

static void	free_texture_list(t_texture **textures)
{
	t_texture	*cursor;
	t_texture	*next;

	cursor = *textures;
	while (cursor != NULL)
	{
		next = cursor->next;
		free(cursor->path);
		free(cursor);
		cursor = next;
	}
	*textures = NULL;
}

static void	free_map(t_map *map)
{
	size_t	row;

	if (map->grid == NULL)
		return ;
	row = 0;
	while (row < map->height)
	{
		free(map->grid[row]);
		++row;
	}
	free(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	cleanup_config(t_config *config)
{
	free_texture_list(&config->textures);
	free_map(&config->map);
	*config = (t_config){0};
}
