#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

#define KEY_ESCAPE 65307
#define EVENT_DESTROY_NOTIFY 17

static int	handle_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app == NULL)
		return (0);
	app->running = false;
	if (app->mlx != NULL)
		mlx_loop_end(app->mlx);
	return (0);
}

static int	handle_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app == NULL)
		return (0);
	if (keycode == KEY_ESCAPE)
		handle_close(app);
	return (0);
}

static int	loop_hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app == NULL || !app->running)
		return (0);
	render_frame(app);
	return (0);
}

static void	release_textures(t_app *app)
{
	t_texture	*cursor;

	if (app->mlx == NULL)
		return ;
	cursor = app->config.textures;
	while (cursor != NULL)
	{
		if (cursor->img != NULL)
		{
			mlx_destroy_image(app->mlx, cursor->img);
			cursor->img = NULL;
		}
		cursor = cursor->next;
	}
}

int	start_application(t_app *app, int argc, char **argv)
{
	app->running = false;
	if (!parse_args(app, argc, argv))
		return (1);
	if (!parse_config(app, argv[1]))
		return (1);
	app->mlx = mlx_init();
	if (app->mlx == NULL)
	{
		write(2, "Error: failed to initialise MiniLibX\n",
			sizeof("Error: failed to initialise MiniLibX\n") - 1);
		return (1);
	}
	app->window = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (app->window == NULL)
	{
		write(2, "Error: failed to create window\n",
			sizeof("Error: failed to create window\n") - 1);
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		app->mlx = NULL;
		return (1);
	}
	app->running = true;
	return (0);
}

void	app_loop(t_app *app)
{
	if (app->mlx == NULL || app->window == NULL)
		return ;
	mlx_loop_hook(app->mlx, loop_hook, app);
	mlx_key_hook(app->window, handle_key, app);
	mlx_hook(app->window, EVENT_DESTROY_NOTIFY, 0, handle_close, app);
	mlx_loop(app->mlx);
}

void	destroy_app(t_app *app)
{
	if (app == NULL)
		return ;
	release_textures(app);
	if (app->window != NULL && app->mlx != NULL)
	{
		mlx_destroy_window(app->mlx, app->window);
		app->window = NULL;
	}
	if (app->mlx != NULL)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		app->mlx = NULL;
	}
	cleanup_config(&app->config);
	app->running = false;
}
