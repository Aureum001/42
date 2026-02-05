#include "cub3d.h"
#include <unistd.h>

static bool	has_cub_extension(const char *path)
{
	size_t	len;

	if (path == NULL)
		return (false);
	len = 0;
	while (path[len] != '\0')
		++len;
	if (len < 5)
		return (false);
	return (path[len - 4] == '.' && path[len - 3] == 'c'
		&& path[len - 2] == 'u' && path[len - 1] == 'b');
}

bool	parse_args(t_app *app, int argc, char **argv)
{
	(void)app;
	if (argc != 2)
	{
		write(2, "Usage: ./cub3d <map.cub>\n", sizeof("Usage: ./cub3d <map.cub>\n") - 1);
		return (false);
	}
	if (!has_cub_extension(argv[1]))
	{
		write(2, "Error: map must end with .cub\n", sizeof("Error: map must end with .cub\n") - 1);
		return (false);
	}
	return (true);
}
