/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:16 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:10:58 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Processes one line from all_lines at index i.
 Returns: 1 = map section ended (break), 0 = continue, -1 = error.
*/
static int	process_line(t_map *map, char **all_lines, int total,
	char ***ml, int *mc, int *mcap, int *in_map, int i)
{
	if (is_empty_line(all_lines[i]))
	{
		if (!*in_map)
			return (0);
		if (check_no_content_after(all_lines, total, i + 1) == -1)
			return (-1);
		return (1);
	}
	if (*in_map || is_map_line(all_lines[i]))
	{
		*in_map = 1;
		if (append_map_line(ml, mc, mcap, all_lines[i]) == -1)
			return (ft_error(ERR_MEM));
		return (0);
	}
	if (parse_header_line(map, all_lines[i]) == -1)
		return (-1);
	return (0);
}

/*
 Frees temporary parse buffers and the map on failure.
 Always returns -1 so callers can chain: return (parse_cleanup(...)).
*/
static int	parse_cleanup(char **all, char **ml, t_map *map)
{
	free_array(all);
	free(ml);
	free_map(map);
	return (-1);
}

/*
 Iterates all lines, dispatching each to header parsing or map collection.
 Returns the number of map lines collected, or -1 on error.
*/
static int	collect_lines(t_map *map, char **all_lines, int total,
	char ***map_lines_out)
{
	char	**map_lines;
	int		map_count, map_cap, in_map, i, ret;

	in_map = 0;
	map_count = 0;
	map_cap = 32;
	map_lines = ft_calloc(map_cap, sizeof(char *));
	if (!map_lines)
		return (ft_error(ERR_MEM));
	i = 0;
	while (i < total)
	{
		ret = process_line(map, all_lines, total,
				&map_lines, &map_count, &map_cap, &in_map, i);
		if (ret == -1)
		{
			free(map_lines);
			return (-1);
		}
		if (ret == 1)
			break ;
		i++;
	}
	*map_lines_out = map_lines;
	return (map_count);
}

/*
 Runs collect, validates headers, builds grid and validates map.
 Frees temporary buffers on failure; keeps map->grid on success.
*/
static int	do_parse(t_map *map, char **all_lines, int total)
{
	char	**map_lines;
	int		map_count;

	map_lines = NULL;
	map_count = collect_lines(map, all_lines, total, &map_lines);
	if (map_count == -1)
		return (parse_cleanup(all_lines, map_lines, map));
	if (headers_complete(map) == -1 || map_count == 0)
	{
		if (map_count == 0)
			ft_error(ERR_MAP);
		return (parse_cleanup(all_lines, map_lines, map));
	}
	if (build_map_grid(map, map_lines, map_count) == -1
		|| validate_map(map) == -1)
		return (parse_cleanup(all_lines, map_lines, map));
	free_array(all_lines);
	free(map_lines);
	return (0);
}

/*
 Entry point for parsing a .cub file.
 Validates extension, reads file, then delegates to do_parse.
 Returns 0 on success, -1 on any error.
*/
int	parse_file(t_game *game, char *path)
{
	int		fd;
	char	**all_lines;
	int		total;

	if (check_extension(path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error(ERR_OPEN));
	all_lines = read_all_lines(fd, &total);
	close(fd);
	if (!all_lines)
		return (ft_error(ERR_MEM));
	ft_bzero(&game->map, sizeof(t_map));
	return (do_parse(&game->map, all_lines, total));
}
