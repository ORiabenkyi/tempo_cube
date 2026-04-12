/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:53 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:50:30 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Computes the minimap context.
** Cell size starts at MINI_CELL and shrinks until the map fits in MINI_MAX.
** Origin is placed so the right edge is MINI_MARGIN px from screen right,
** and the top edge is MINI_MARGIN px from screen top.
*/
static t_mctx	make_ctx(t_game *game)
{
	t_mctx	c;
	int		cz;

	cz = MINI_CELL;
	while (cz > 1
		&& (game->map.cols * cz > MINI_MAX
			|| game->map.rows * cz > MINI_MAX))
		cz--;
	c.cz = cz;
	c.ox = SCREEN_W - MINI_MARGIN - game->map.cols * cz;
	c.oy = MINI_MARGIN;
	return (c);
}

/*
** Draws every cell of the map grid as a filled rectangle.
*/
static void	draw_cells(t_game *game, t_mctx *c)
{
	int	mx;
	int	my;
	int	col_len;

	my = 0;
	while (my < game->map.rows)
	{
		col_len = (int)ft_strlen(game->map.grid[my]);
		mx = 0;
		while (mx < col_len)
		{
			draw_rect(game,
				c->ox + mx * c->cz,
				c->oy + my * c->cz,
				c->cz - 1,
				c->cz - 1,
				cell_color(game, mx, my));
			mx++;
		}
		my++;
	}
}

/*
** Draws the player as a 3x3 red dot and a short white direction line.
*/
static void	draw_player(t_game *game, t_mctx *c)
{
	t_player	*p;
	int			px;
	int			py;
	int			i;
	int			ex;
	int			ey;

	p = &game->player;
	px = c->ox + (int)(p->pos_x * c->cz);
	py = c->oy + (int)(p->pos_y * c->cz);
	draw_rect(game, px - 1, py - 1, 3, 3, 0xFF0000FF);
	ex = px + (int)(p->dir_x * c->cz * 1.5);
	ey = py + (int)(p->dir_y * c->cz * 1.5);
	i = 0;
	while (i <= c->cz)
	{
		int	lx;
		int	ly;

		lx = px + (ex - px) * i / c->cz;
		ly = py + (ey - py) * i / c->cz;
		if (lx >= 0 && lx < SCREEN_W && ly >= 0 && ly < SCREEN_H)
			mlx_put_pixel(game->image, lx, ly, 0xFFFFFFFF);
		i++;
	}
}

/*
** Draws the minimap in the top-right corner if show_minimap is set.
*/
void	draw_minimap(t_game *game)
{
	t_mctx	c;

	if (!game->show_minimap)
		return ;
	c = make_ctx(game);
	draw_cells(game, &c);
	draw_player(game, &c);
}
