/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:39 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:39 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Initialises ray direction and DDA step values for screen column x.
 camera_x maps [0, SCREEN_W-1] to [-1, +1] (left to right).
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	t_player	*p;

	p = &game->player;
	ray->is_door = 0;
	ray->cam_x = 2.0 * x / SCREEN_W - 1.0;
	ray->dir_x = p->dir_x + p->plane_x * ray->cam_x;
	ray->dir_y = p->dir_y + p->plane_y * ray->cam_x;
	ray->map_x = (int)p->pos_x;
	ray->map_y = (int)p->pos_y;
	ray->ddist_x = (ray->dir_x == 0) ? 1e30 : fabs(1.0 / ray->dir_x);
	ray->ddist_y = (ray->dir_y == 0) ? 1e30 : fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sdist_x = (p->pos_x - ray->map_x) * ray->ddist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sdist_x = (ray->map_x + 1.0 - p->pos_x) * ray->ddist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sdist_y = (p->pos_y - ray->map_y) * ray->ddist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sdist_y = (ray->map_y + 1.0 - p->pos_y) * ray->ddist_y;
	}
}

/*
 Digital Differential Analysis: steps through the grid until a solid cell
 is hit ('1' wall or closed 'D' door).
 Sets ray->side: 0 if hit on X axis, 1 if hit on Y axis.
 Sets ray->is_door: 1 if the stopping cell is a door (for darker rendering).
 Open doors ('D' with state DOOR_OPEN) are transparent — ray continues.

  Цифровий диференціальний аналіз: проходить по сітці, доки не натрапить на суцільну комірку
  (стіна зі значенням «1» або закриті двері зі значенням «D»).
  Встановлює параметр ray->side: 0, якщо зіткнення відбулося по осі X, 1 — по осі Y.
  Встановлює параметр ray->is_door: 1, якщо комірка, на якій зупинився промінь, є дверима (для більш темного візуалізування).
  Відкриті двері (зі значенням «D» та станом DOOR_OPEN) є прозорими — промінь проходить далі.

*/
void	dda(t_game *game, t_ray *ray)
{
	char	**grid;
	int		rows;
	int		col_len;
	char	cell;
	t_door	*door;

	grid = game->map.grid;
	rows = game->map.rows;
	while (1)
	{
		if (ray->sdist_x < ray->sdist_y)
		{
			ray->sdist_x += ray->ddist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sdist_y += ray->ddist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= rows || ray->map_x < 0)
			break ;
		col_len = (int)ft_strlen(grid[ray->map_y]);
		if (ray->map_x >= col_len)
			break ;
		cell = grid[ray->map_y][ray->map_x];
		if (cell == '1')
			break ;
		if (cell == 'D')
		{
			door = find_door(&game->map, ray->map_x, ray->map_y);
			if (!door || door->state == DOOR_CLOSED)
			{
				ray->is_door = 1;
				break ;
			}
		}
	}
}

/*
** Computes perpendicular wall distance, wall height on screen, and which
** texture column to sample.
**
** Texture selection (coordinate system: X=east+, Y=south+):
**   side==0, step_x>0  → ray went east, hit WEST face  → WE texture
**   side==0, step_x<0  → ray went west, hit EAST face  → EA texture
**   side==1, step_y>0  → ray went south, hit NORTH face → NO texture
**   side==1, step_y<0  → ray went north, hit SOUTH face → SO texture
*/
void	calc_wall(t_game *game, t_ray *ray)
{
	t_player		*p;
	double			wall_x;
	mlx_texture_t	*tex;

	p = &game->player;
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
		ray->tex_idx = (ray->step_x > 0) ? TEX_WE : TEX_EA;
	else
		ray->tex_idx = (ray->step_y > 0) ? TEX_NO : TEX_SO;
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
