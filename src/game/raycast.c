/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:36 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:31:57 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Reads one RGBA pixel from texture at (x,y).
 If door is non-zero, halves each RGB channel (darkens the pixel).
*/
static uint32_t	tex_pixel(mlx_texture_t *t, int x, int y, int door)
{
	int			idx;
	uint32_t	col;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	idx = (y * (int)t->width + x) * (int)t->bytes_per_pixel;
	col = ((uint32_t)t->pixels[idx] << 24)
		| ((uint32_t)t->pixels[idx + 1] << 16)
		| ((uint32_t)t->pixels[idx + 2] << 8)
		| t->pixels[idx + 3];
	if (!door)
		return (col);
	r = ((col >> 24) & 0xFF) >> 1;
	g = ((col >> 16) & 0xFF) >> 1;
	b = ((col >> 8) & 0xFF) >> 1;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/*
 Samples the wall texture at the current vertical position and
 draws the pixel. Advances tex_pos by step for the next row.

 Зчитує текстуру стіни у поточній вертикальній позиції та 
 малює піксель. Збільшує значення tex_pos на крок для наступного рядка.
*/
static void	draw_wall_pixel(t_game *game, t_ray *ray, int x, int y,
	double *tex_pos, double step, mlx_texture_t *tex)
{
	int	tex_y;

	tex_y = (int)*tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = (int)tex->height - 1;
	*tex_pos += step;
	mlx_put_pixel(game->image, x, y,
		tex_pixel(tex, ray->tex_x, tex_y, ray->is_door));
}

/*
 Draws one vertical screen column:
   - ceiling color above the wall
   - textured (optionally darkened) wall strip
   - floor color below the wall
*/
static void	draw_column(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				y;

	tex = game->tex[ray->tex_idx];
	step = (double)tex->height / ray->line_h;
	tex_pos = (ray->draw_start - SCREEN_H / 2 + ray->line_h / 2) * step;
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < ray->draw_start)
			mlx_put_pixel(game->image, x, y, game->map.ceil_col);
		else if (y > ray->draw_end)
			mlx_put_pixel(game->image, x, y, game->map.floor_col);
		else
			draw_wall_pixel(game, ray, x, y, &tex_pos, step, tex);
		y++;
	}
}

/*
 Main render function — called every frame.
 Casts one ray per screen column and draws the result.
*/
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(game, &ray, x);
		dda(game, &ray);
		calc_wall(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}
