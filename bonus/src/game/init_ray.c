/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:39 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 14:31:49 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	feel_step_x(t_player *p, t_ray *ray)
{
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
}

static void	feel_step_y(t_player *p, t_ray *ray)
{
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
	if (ray->dir_x == 0)
		ray->ddist_x = 1e30;
	else
		ray->ddist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->ddist_y = 1e30;
	else
		ray->ddist_y = fabs(1.0 / ray->dir_y);
	feel_step_x(p, ray);
	feel_step_y(p, ray);
}
