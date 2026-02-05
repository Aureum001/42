#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_app	app;

	app = (t_app){0};
	if (start_application(&app, argc, argv) != 0)
	{
		destroy_app(&app);
		return (1);
	}
	enable_bonus_hooks(&app);
	app_loop(&app);
	destroy_app(&app);
	return (0);
}
