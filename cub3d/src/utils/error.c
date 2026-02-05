#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

static size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		++len;
	return (len);
}

void	error_exit(t_app *app, const char *message)
{
	size_t	len;

	write(2, "Error\n", 6);
	if (message != NULL)
	{
		len = str_len(message);
		if (len > 0)
		{
			write(2, message, len);
			write(2, "\n", 1);
		}
	}
	destroy_app(app);
	exit(EXIT_FAILURE);
}
