/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:33 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:34 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Called every frame via the game loop.
** Advances each open door's timer by delta_time.
** Auto-closes the door when DOOR_CLOSE_TIME seconds have elapsed and
** the player is not standing in the door's cell.
*/
void	update_doors(t_game *game)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < game->map.door_count)
	{
		door = &game->map.doors[i];
		if (door->state == DOOR_OPEN)
		{
			door->timer += game->mlx->delta_time;
			if (door->timer >= DOOR_CLOSE_TIME
				&& !player_in_door(game, door))
			{
				door->state = DOOR_CLOSED;
				door->timer = 0.0;
			}
		}
		i++;
	}
}
