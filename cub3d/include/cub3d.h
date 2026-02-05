#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>

/*
** MinilibX headers are expected to live under lib/minilibx-linux. The compile-time
** guard below lets the template build before the library is present.
*/
# ifdef __has_include
#  if __has_include("mlx.h")
#   include "mlx.h"
#  else
typedef void	*t_mlx_ptr;
typedef void	*t_mlx_image;
#  endif
# else
#  include "mlx.h"
# endif

# define WIN_WIDTH  1280
# define WIN_HEIGHT 720
# define FOV_DEG    66.0

typedef struct s_texture
{
	char		*path;
	void		*img;
	int			width;
	int			height;
	struct s_texture *next;
}t_texture;

typedef struct s_map
{
	char		**grid;
	size_t		width;
	size_t		height;
}t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}t_player;

typedef struct s_config
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_texture	*textures;
	t_map		map;
	t_player	player;
}t_config;

typedef struct s_app
{
	void		*mlx;
	void		*window;
	bool		running;
	t_config	config;
}t_app;

/* core */
int	start_application(t_app *app, int argc, char **argv);
void	app_loop(t_app *app);
void	destroy_app(t_app *app);

/* parser */
bool	parse_args(t_app *app, int argc, char **argv);
bool	parse_config(t_app *app, const char *path);

/* render */
void	render_frame(t_app *app);

/* utils */
void	error_exit(t_app *app, const char *message);
void	cleanup_config(t_config *config);

/* bonus */
void	enable_bonus_hooks(t_app *app);

#endif
