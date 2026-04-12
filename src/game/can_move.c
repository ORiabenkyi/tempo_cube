/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:17 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:37:37 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	cell_walkable(t_game *game, int nx, int ny)
{
	char	c;
	t_door	*door;

	if (ny < 0 || nx < 0 || ny >= game->map.rows)
		return (0);
	if (nx >= (int)ft_strlen(game->map.grid[ny]))
		return (0);
	c = game->map.grid[ny][nx];
	if (c == '1' || c == ' ')
		return (0);
	if (c == 'D')
	{
		door = find_door(&game->map, nx, ny);
		if (!door || door->state == DOOR_OPEN)
			return (1);
		return ((int)game->player.pos_x == nx
			&& (int)game->player.pos_y == ny);
	}
	return (1);
}

int	can_move(t_game *game, double new_x, double new_y)
{
	return (cell_walkable(game, (int)(new_x - PLAYER_MARGIN),
		(int)(new_y - PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x + PLAYER_MARGIN),
			(int)(new_y - PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x - PLAYER_MARGIN),
			(int)(new_y + PLAYER_MARGIN))
		&& cell_walkable(game, (int)(new_x + PLAYER_MARGIN),
			(int)(new_y + PLAYER_MARGIN)));
}
