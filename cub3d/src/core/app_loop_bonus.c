#include "cub3d.h"

#define MOUSE_LEFT_BUTTON 1

static int	handle_mouse(int button, int x, int y, void *param)
{
	t_app	*app;
	int		message_color;

	(void)x;
	(void)y;
	app = (t_app *)param;
	if (app == NULL || app->mlx == NULL || app->window == NULL)
		return (0);
	if (button == MOUSE_LEFT_BUTTON)
	{
		message_color = 0x00FF5555;
		mlx_string_put(app->mlx, app->window, 24, 64,
			message_color, "Bonus: left click detected");
	}
	return (0);
}

void	enable_bonus_hooks(t_app *app)
{
	if (app == NULL || app->mlx == NULL || app->window == NULL)
		return ;
	mlx_mouse_hook(app->window, handle_mouse, app);
}
