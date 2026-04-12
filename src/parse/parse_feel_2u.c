/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_feel_2u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:02 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 13:39:10 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_feel_north(t_map *map, char *line)
{
	if (map->no)
		return (ft_error("Duplicate NO field"));
	map->no = ft_strtrim(line, " \t");
	if (!map->no || !*map->no)
		return (ft_error("NO: missing texture path"));
	return (0);
}

int	parse_feel_south(t_map *map, char *line)
{
	if (map->so)
		return (ft_error("Duplicate SO field"));
	map->so = ft_strtrim(line, " \t");
	if (!map->so || !*map->so)
		return (ft_error("SO: missing texture path"));
	return (0);
}

int	parse_feel_east(t_map *map, char *line)
{
	if (map->ea)
		return (ft_error("Duplicate EA field"));
	map->ea = ft_strtrim(line, " \t");
	if (!map->ea || !*map->ea)
		return (ft_error("EA: missing texture path"));
	return (0);
}

int	parse_feel_west(t_map *map, char *line)
{
	if (map->we)
		return (ft_error("Duplicate WE field"));
	map->we = ft_strtrim(line, " \t");
	if (!map->we || !*map->we)
		return (ft_error("WE: missing texture path"));
	return (0);
}
