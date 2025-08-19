/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:11:42 by ancanale          #+#    #+#             */
/*   Updated: 2025/08/13 09:33:37 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	color_comp(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

static void	fill_row(t_rowctx *c, int y)
{
	int		x;
	int		off;

	x = 0;
	while (x < c->w)
	{
		off = (y * c->sz) + (x * (c->bpp / 8));
		c->data[off + 0] = color_comp(c->color, 0);
		c->data[off + 1] = color_comp(c->color, 8);
		c->data[off + 2] = color_comp(c->color, 16);
		x++;
	}
}

void	create_hud_image(t_game_bonus *g, t_hudspec spec)
{
	int			bpp;
	int			sz;
	int			en;
	int			y;
	t_rowctx	ctx;

	g->img_hud = mlx_new_image(g->base.mlx, spec.w, spec.h);
	if (!g->img_hud)
		error_exit("HUD image creation failed");
	ctx.data = mlx_get_data_addr(g->img_hud, &bpp, &sz, &en);
	ctx.w = spec.w;
	ctx.bpp = bpp;
	ctx.sz = sz;
	ctx.color = spec.color;
	y = 0;
	while (y < spec.h)
	{
		fill_row(&ctx, y);
		y++;
	}
}

void	render_moves_on_screen(t_game_bonus *game)
{
	char	buf[32];

	snprintf(buf, sizeof(buf), "Moves: %d", game->base.moves);
	mlx_string_put(game->base.mlx, game->base.win, 10, 18, 0xFFFFFF, buf);
}
