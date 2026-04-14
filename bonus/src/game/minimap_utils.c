/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:55 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 16:39:32 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Fills a rectangle [px, px+w] x [py, py+h] with color on game->image.
 Clips to screen bounds.
*/
void	draw_rect(t_game *game, int mx, int my, t_mctx *c)
{
	int			x;
	int			y;
	int			px;
	int			py;
	uint32_t	col;

	col = cell_color(game, mx, my);
	px = c->ox + mx * c->cz;
	py = c->oy + my * c->cz;
	y = py;
	while (y < py + c->cz - 1)
	{
		x = px;
		while (x < px + c->cz - 1)
		{
			if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
				mlx_put_pixel(game->image, x, y, col);
			x++;
		}
		y++;
	}
}

void	draw_mini_player(t_game *game, int px, int py, uint32_t col)
{
	int	w;
	int	h;
	int	x;
	int	y;

	w = 3;
	h = 3;
	y = py;
	while (y < py + h)
	{
		x = px;
		while (x < px + w)
		{
			if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
				mlx_put_pixel(game->image, x, y, col);
			x++;
		}
		y++;
	}
}
/*
 Returns the color for a single map cell for the minimap.
   '1'        → dark grey (wall)
   'D' closed → brown
   'D' open   → gold
   ' '        → transparent black
   other      → medium grey (floor / player spawn)
*/

uint32_t	cell_color(t_game *game, int mx, int my)
{
	char	c;
	t_door	*door;

	c = game->map.grid[my][mx];
	if (c == '1')
		return (0x333333FF);
	if (c == ' ')
		return (0x00000088);
	if (c == 'D')
	{
		door = find_door(&game->map, mx, my);
		if (!door || door->state == DOOR_CLOSED)
			return (0x8B4513FF);
		return (0xFFD700FF);
	}
	return (0x888888FF);
}
