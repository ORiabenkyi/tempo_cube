/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:39 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 15:57:04 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	select_direction(int val, int a, int b)
{
	if (val > 0)
		return (a);
	return (b);
}
/*
 Computes perpendicular wall distance, wall height on screen, and which
 texture column to sample.

 Texture selection (coordinate system: X=east+, Y=south+):
   side==0, step_x>0  → ray went east, hit WEST face  → WE texture
   side==0, step_x<0  → ray went west, hit EAST face  → EA texture
   side==1, step_y>0  → ray went south, hit NORTH face → NO texture
   side==1, step_y<0  → ray went north, hit SOUTH face → SO texture
*/

static void	prepair_state(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->sdist_x - ray->ddist_x;
	else
		ray->wall_dist = ray->sdist_y - ray->ddist_y;
	ray->line_h = (int)(SCREEN_H / ray->wall_dist);
	ray->draw_start = -ray->line_h / 2 + SCREEN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + SCREEN_H / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
	if (ray->side == 0)
		ray->tex_idx = select_direction(ray->step_x, TEX_WE, TEX_EA);
	else
		ray->tex_idx = select_direction(ray->step_y, TEX_NO, TEX_SO);
}

void	calc_wall(t_game *game, t_ray *ray)
{
	t_player		*p;
	double			wall_x;
	mlx_texture_t	*tex;

	p = &game->player;
	prepair_state(ray);
	if (ray->side == 0)
		wall_x = p->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = p->pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex = game->tex[ray->tex_idx];
	ray->tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = (int)tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = (int)tex->width - ray->tex_x - 1;
}
