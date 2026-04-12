/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:39 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 15:48:31 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	make_step(t_ray *ray)
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
}
/*
 Digital Differential Analysis: steps through the grid until a solid cell
 is hit ('1' wall or closed 'D' door).
 Sets ray->side: 0 if hit on X axis, 1 if hit on Y axis.
 Sets ray->is_door: 1 if the stopping cell is a door (for darker rendering).
 Open doors ('D' with state DOOR_OPEN) are transparent — ray continues.

  Цифровий диференціальний аналіз: проходить по сітці, доки не натрапить 
  на суцільну комірку
  (стіна зі значенням «1» або закриті двері зі значенням «D»).
  Встановлює параметр ray->side: 0, якщо зіткнення відбулося по осі X, 
  1 — по осі Y.
  Встановлює параметр ray->is_door: 1, якщо комірка, на якій зупинився 
  промінь, є дверима (для більш темного візуалізування).
  Відкриті двері (зі значенням «D» та станом DOOR_OPEN) є прозорими — промінь
  проходить далі.
*/

void	dda(t_game *game, t_ray *ray)
{
	char	**grid;
	int		rows;
	t_door	*door;

	grid = game->map.grid;
	rows = game->map.rows;
	while (1)
	{
		make_step(ray);
		if (ray->map_y < 0 || ray->map_y >= rows || ray->map_x < 0)
			break ;
		if (ray->map_x >= (int)ft_strlen(grid[ray->map_y]))
			break ;
		if (grid[ray->map_y][ray->map_x] == '1')
			break ;
		if (grid[ray->map_y][ray->map_x] == 'D')
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
