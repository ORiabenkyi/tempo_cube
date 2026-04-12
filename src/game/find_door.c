/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:29 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:31 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Linear search through the doors array for a door at grid cell (x, y).
** Returns a pointer to the door, or NULL if not found.
*/
t_door	*find_door(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}
