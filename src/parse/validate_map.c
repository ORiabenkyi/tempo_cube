/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:55 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:41:15 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


/*
** Returns the character at grid[y][x], or ' ' if out of bounds.
** Used so the closed-wall check treats the outside as "open space".
*/
static char	safe_cell(char **grid, int rows, int y, int x)
{
	int	len;

	if (y < 0 || y >= rows || x < 0)
		return (' ');
	len = (int)ft_strlen(grid[y]);
	if (x >= len)
		return (' ');
	return (grid[y][x]);
}

static int	feel_player(t_map *map, int x, int y, char c)
{
	map->player_x = x;
	map->player_y = y;
	map->player_dir = c;
	return (1);
}

/*
 Iterates every cell in the grid:
   - Rejects characters outside the valid set.
   - Counts player spawn markers (N/S/E/W).
 Stores the player position and direction in map on success.
 Returns 0 on success, -1 on error.
*/
static int	check_chars_and_player(t_map *map)
{
	int		player_count;
	int		y;
	int		x;
	char	c;

	player_count = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (!ft_strchr("01DNSEW ", c))
				return (ft_error(ERR_CHAR));
			if (ft_strchr("NSEW", c))
				player_count += feel_player(map, x, y, c);
			x++;
		}
		y++;
	}
	if (player_count == 0 || player_count > 1)
		return (ft_error(ERR_PLAYER));
	return (0);
}

/*
** For every traversable cell (0 or player spawn), checks that all four
** cardinal neighbours exist and are not space / out-of-bounds.
** Returns 0 if closed, -1 with error message if not.
*/
static int	check_closed(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == '0' || ft_strchr("NSEW", c))
			{
				if (safe_cell(map->grid, map->rows, y - 1, x) == ' '
					|| safe_cell(map->grid, map->rows, y + 1, x) == ' '
					|| safe_cell(map->grid, map->rows, y, x - 1) == ' '
					|| safe_cell(map->grid, map->rows, y, x + 1) == ' ')
					return (ft_error(ERR_CLOSED));
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
** Top-level map validator called after build_map_grid.
** Runs character/player check, wall-closure check, then door collection.
** Returns 0 on success, -1 on any validation failure.
*/
int	validate_map(t_map *map)
{
	if (map->rows == 0)
		return (ft_error("Map is empty"));
	if (check_chars_and_player(map) == -1)
		return (-1);
	if (check_closed(map) == -1)
		return (-1);
	if (collect_doors(map) == -1)
		return (-1);
	return (0);
}
