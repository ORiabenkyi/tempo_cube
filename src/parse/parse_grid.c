/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:32 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:23:34 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Adds a map line pointer to the map_lines buffer, growing it if needed.
** map_lines elements point into all_lines (not owned).
** Returns 0 on success, -1 on allocation failure.
*/
int	append_map_line(char ***map_lines, int *map_count, int *map_cap,
	char *line)
{
	char	**tmp;

	if (*map_count >= *map_cap - 2)
	{
		*map_cap *= 2;
		tmp = ft_calloc(*map_cap, sizeof(char *));
		if (!tmp)
			return (-1);
		ft_memcpy(tmp, *map_lines, sizeof(char *) * (*map_count));
		free(*map_lines);
		*map_lines = tmp;
	}
	(*map_lines)[(*map_count)++] = line;
	return (0);
}

/*
** Builds map->grid from the array of raw map lines.
** Each line is duplicated so the grid owns its memory.
** Returns 0 on success, -1 on allocation failure.
*/
int	build_map_grid(t_map *map, char **lines, int count)
{
	int	i;
	int	len;

	map->rows = count;
	map->cols = 0;
	map->grid = ft_calloc(count + 1, sizeof(char *));
	if (!map->grid)
		return (ft_error(ERR_MEM));
	i = 0;
	while (i < count)
	{
		map->grid[i] = ft_strdup(lines[i]);
		if (!map->grid[i])
		{
			free_array(map->grid);
			map->grid = NULL;
			return (ft_error(ERR_MEM));
		}
		len = (int)ft_strlen(map->grid[i]);
		if (len > map->cols)
			map->cols = len;
		i++;
	}
	return (0);
}

/*
** First pass: counts 'D' cells in the grid.
*/
static int	count_doors(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/*
** Second pass: fills map->doors with coordinates and initial state.
*/
static void	fill_doors(t_map *map)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'D')
			{
				map->doors[i].x = x;
				map->doors[i].y = y;
				map->doors[i].state = DOOR_CLOSED;
				map->doors[i].timer = 0.0;
				i++;
			}
			x++;
		}
		y++;
	}
}

/*
** Scans the validated grid and builds the map->doors array.
** Returns 0 on success, -1 on allocation failure.
*/
int	collect_doors(t_map *map)
{
	map->door_count = count_doors(map);
	if (map->door_count == 0)
		return (0);
	map->doors = ft_calloc(map->door_count, sizeof(t_door));
	if (!map->doors)
		return (ft_error(ERR_MEM));
	fill_doors(map);
	return (0);
}
