/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:25:13 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:09:14 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	feel_player_north(t_player *p, char player_dir)
{
	if (player_dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
}

static void	feel_player_south(t_player *p, char player_dir)
{
	if (player_dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

static void	feel_player_east(t_player *p, char player_dir)
{
	if (player_dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
}

static void	feel_player_west(t_player *p, char player_dir)
{
	if (player_dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

/*
** Sets player direction and camera plane based on spawn character.
** Camera plane length 0.66 gives ~66° FOV.
** Coordinate system: X = east (+), Y = south (+).
**
**   N → dir (0,-1)  plane (0.66, 0)
**   S → dir (0, 1)  plane (-0.66, 0)
**   E → dir (1, 0)  plane (0, 0.66)
**   W → dir (-1, 0) plane (0, -0.66)
*/
void	init_player(t_game *game)
{
	t_player	*p;
	t_map		*m;

	p = &game->player;
	m = &game->map;
	p->pos_x = m->player_x + 0.5;
	p->pos_y = m->player_y + 0.5;
	feel_player_north(p, m->player_dir);
	feel_player_south(p, m->player_dir);
	feel_player_east(p, m->player_dir);
	feel_player_west(p, m->player_dir);
}
