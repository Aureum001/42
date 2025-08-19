/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:08:46 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/19 09:34:36 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "so_long.h"

# define ENEMY 'X'

typedef struct s_enemy
{
	int				x;
	int				y;
	int				direction;
	int				prev_x;
	int				prev_y;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_game_bonus
{
	t_game	base;
	t_enemy	*enemies;
	void	*img_enemy[6];
	void	*img_hud;
	int		moves_on_screen;
	int		game_over;
	int		enemy_tick;
	int		enemy_speed;
	long	enemy_last_ms;
	int		enemy_interval_ms;
	int		static_drawn;
	int		prev_player_x;
	int		prev_player_y;
}	t_game_bonus;

void	render_moves_on_screen(t_game_bonus *game);
void	update_enemies(t_game_bonus *game);
void	check_enemy_collision(t_game_bonus *game);
void	add_enemy(t_game_bonus *game, int x, int y);
long	current_time_ms(void);
void	render_game_bonus(t_game_bonus *game);
int		enemy_update_hook(void *param);
void	load_images_bonus(t_game_bonus *game);
int		key_hook_bonus(int keycode, void *param);
int		cleanup_and_exit_bonus(void *param);

typedef struct s_hudspec
{
	int	w;
	int	h;
	int	color;
}	t_hudspec;

typedef struct s_rowctx
{
	char	*data;
	int		w;
	int		bpp;
	int		sz;
	int		color;
}	t_rowctx;

void	create_hud_image(t_game_bonus *g, t_hudspec spec);
void	parse_map_bonus(t_game_bonus *game);
void	scan_map_for_validation(t_game_bonus *g);
int		validate_map(t_game *game);
void	free_enemies(t_game_bonus *game);

#endif
