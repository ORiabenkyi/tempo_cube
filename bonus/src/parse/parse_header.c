/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:41 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 13:42:15 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Validates that str contains only digits (and leading spaces).
 Used to reject values like "9abc" or "" before ft_atoi.
*/
static int	is_valid_uint(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/*
 Parses a color string of the form "R,G,B" into t_color.
 Returns 0 on success, -1 on any format or range error.
*/
int	parse_color(char *str, t_color *c)
{
	char	**parts;

	while (*str == ' ' || *str == '\t')
		str++;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_array(parts);
		return (-1);
	}
	if (!is_valid_uint(parts[0]) || !is_valid_uint(parts[1])
		|| !is_valid_uint(parts[2]))
	{
		free_array(parts);
		return (-1);
	}
	c->r = ft_atoi(parts[0]);
	c->g = ft_atoi(parts[1]);
	c->b = ft_atoi(parts[2]);
	free_array(parts);
	if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255
		|| c->b < 0 || c->b > 255)
		return (-1);
	return (0);
}

/*
 Parses a single header line and stores the result in map.
 Handles: NO, SO, WE, EA (texture paths), F and C (colors).
 Returns 0 on success, -1 on error.
*/
int	parse_header_line(t_map *map, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_feel_north(map, line + 3));
	else if (!ft_strncmp(line, "SO ", 3))
		return (parse_feel_south(map, line + 3));
	else if (!ft_strncmp(line, "WE ", 3))
		return (parse_feel_west(map, line + 3));
	else if (!ft_strncmp(line, "EA ", 3))
		return (parse_feel_east(map, line + 3));
	else if (!ft_strncmp(line, "F ", 2))
		return (parse_feel_floor(map, line + 2));
	else if (!ft_strncmp(line, "C ", 2))
		return (parse_feel_ceiling(map, line + 2));
	else
		return (ft_error(ERR_FIELD));
	return (0);
}

/*
 Checks that all 6 required header fields were found.
 Returns 0 if complete, -1 with error message if not.
*/
int	headers_complete(t_map *map)
{
	if (!map->no || !map->so || !map->we || !map->ea)
		return (ft_error("Missing texture identifier (NO/SO/WE/EA)"));
	if (!map->has_floor || !map->has_ceiling)
		return (ft_error("Missing color identifier (F/C)"));
	return (0);
}
