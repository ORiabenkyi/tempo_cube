/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_feel_1u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:02 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:39:11 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Converts a t_color into a packed RGBA uint32_t (alpha = 0xFF).
*/
static uint32_t	color_to_rgba(t_color c)
{
	return ((c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF);
}

int	parse_feel_ceiling(t_map *map, char *line)
{
	if (map->has_ceiling)
		return (ft_error("Duplicate C (ceiling color) field"));
	if (parse_color(line, &(map->ceiling)) == -1)
		return (ft_error(ERR_COLOR));
	map->has_ceiling = 1;
	map->ceil_col = color_to_rgba(map->ceiling);
	return (0);
}

int	parse_feel_floor(t_map *map, char *line)
{
	if (map->has_floor)
		return (ft_error("Duplicate F (floor color) field"));
	if (parse_color(line, &(map->floor)) == -1)
		return (ft_error(ERR_COLOR));
	map->has_floor = 1;
	map->floor_col = color_to_rgba(map->floor);
	return (0);
}
