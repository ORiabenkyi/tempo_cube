/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:48 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:50 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Moves the player forward (positive speed) or backward (negative speed)
** along their direction vector.  X and Y are checked independently to
** allow sliding along walls.
*/
void	move_forward(t_game *game, double speed)
{
	t_player	*p;

	p = &game->player;
	if (can_move(game, p->pos_x + p->dir_x * speed, p->pos_y))
		p->pos_x += p->dir_x * speed;
	if (can_move(game, p->pos_x, p->pos_y + p->dir_y * speed))
		p->pos_y += p->dir_y * speed;
}

/*
** Strafes the player left (positive speed) or right (negative speed).
**
** Coordinate system: X = east (+), Y = south (+).
** For direction (dx, dy), the left-strafe vector is (dy, -dx):
**   facing east  (1,0)  → left = (0,-1) = north  ✓
**   facing north (0,-1) → left = (-1,0) = west   ✓
*/
void	strafe(t_game *game, double speed)
{
	t_player	*p;
	double		sx;
	double		sy;

	p = &game->player;
	sx = p->dir_y * speed;
	sy = -p->dir_x * speed;
	if (can_move(game, p->pos_x + sx, p->pos_y))
		p->pos_x += sx;
	if (can_move(game, p->pos_x, p->pos_y + sy))
		p->pos_y += sy;
}

/*
** Rotates the player direction and camera plane by angle (radians).
** Positive angle → clockwise on screen (right turn in Y-down coords).
*/
void	rotate(t_game *game, double angle)
{
	t_player	*p;
	double		cos_a;
	double		sin_a;
	double		old_dx;
	double		old_px;

	p = &game->player;
	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dx = p->dir_x;
	old_px = p->plane_x;
	p->dir_x = p->dir_x * cos_a - p->dir_y * sin_a;
	p->dir_y = old_dx * sin_a + p->dir_y * cos_a;
	p->plane_x = p->plane_x * cos_a - p->plane_y * sin_a;
	p->plane_y = old_px * sin_a + p->plane_y * cos_a;
}
