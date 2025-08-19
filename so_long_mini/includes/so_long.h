/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:08:49 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 11:35:24 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define TILE_SIZE 80

# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		player_count;
	int		exit_count;
	int		moves;
	void	*img_idle[4];
	int		player_frame;
	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_collectible;
}	t_game;

typedef struct s_ff
{
	int	collects;
	int	exit_found;
	int	width;
	int	height;
}	t_ff;

int		main(int argc, char **argv);

int		load_map(t_game *game, const char *filename);
int		cleanup_and_exit(void *param);
void	free_map(char **map);
int		validate_map(t_game *game);
void	set_player_and_collectibles(t_game *game);
void	flood_fill(char **map, int x, int y, t_ff *st);
char	**copy_map(char **map, int height);
void	free_map_copy(char **map, int height);
void	gnl_drain(int fd);

void	load_images(t_game *game);

void	render_game(t_game *game);

int		key_hook(int keycode, void *param);

void	error_exit(const char *msg);

void	cleanup(t_game *game);

int		idle_anim_loop(void *param);

#endif
