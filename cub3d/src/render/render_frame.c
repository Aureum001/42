#include "cub3d.h"

#define BOX_WIDTH 160
#define BOX_HEIGHT 80

void	render_frame(t_app *app)
{
	static int	offset;
	int			x;
	int			y;
	int			box_color;

	if (app->mlx == NULL || app->window == NULL)
		return ;
	mlx_clear_window(app->mlx, app->window);
	box_color = 0x0077CCFF;
	y = 200;
	while (y < 200 + BOX_HEIGHT && y < WIN_HEIGHT)
	{
		x = 200;
		while (x < 200 + BOX_WIDTH && x < WIN_WIDTH)
		{
			mlx_pixel_put(app->mlx, app->window,
				(x + offset) % WIN_WIDTH, y, box_color);
			++x;
		}
		++y;
	}
	mlx_string_put(app->mlx, app->window, 24, 32, 0x00FFFFFF,
		"MiniLibX window test - press ESC to exit");
	offset = (offset + 4) % WIN_WIDTH;
}
