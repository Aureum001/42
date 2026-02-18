#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

bool	parse_config(t_app *app, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: cannot open map file\n", sizeof("Error: cannot open map file\n") - 1);
		return (false);
	}
	/*
	** TODO: read identifiers (NO/SO/EA/WE, F, C) and map layout.
	** Store data into app->config.
	*/
	close(fd);
	app->config.player.pos_x = 3.0;
	app->config.player.pos_y = 3.0;
	app->config.player.dir_x = -1.0;
	app->config.player.dir_y = 0.0;
	app->config.player.plane_x = 0.0;
	app->config.player.plane_y = 0.66;
	app->config.floor_color = 0x00333333;
	app->config.ceiling_color = 0x00AAAAAA;
	return (true);
}
