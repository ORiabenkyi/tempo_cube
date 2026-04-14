/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:16 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 14:07:52 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
 Processes one line from all_lines at index i.
 Returns: 1 = map section ended (break), 0 = continue, -1 = error.
 al = all_lines
*/
static int	process_line(t_map *map, char **al, char ***ml, int i)
{
	if (is_empty_line(al[i]))
	{
		if (!map->in_map)
			return (0);
		if (check_no_content_after(al, map->total, i + 1) == -1)
			return (-1);
		return (1);
	}
	if (map->in_map || is_map_line(al[i]))
	{
		map->in_map = 1;
		if (append_map_line(ml, &map->map_count, &map->map_cap, al[i]) == -1)
			return (ft_error(ERR_MEM));
		return (0);
	}
	if (parse_header_line(map, al[i]) == -1)
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
 mlo = map_lines_out 

 Проходить по всіх рядках, направляючи кожен із них на аналіз заголовка або
 до колекції мап.
 Повертає кількість зібраних рядків мап або -1 у разі помилки.
*/
static int	collect_lines(t_map *map, char **all_lines,	char ***mlo)
{
	char	**map_lines;
	int		i;
	int		ret;

	map->map_cap = 32;
	map_lines = ft_calloc(map->map_cap, sizeof(char *));
	if (!map_lines)
		return (ft_error(ERR_MEM));
	i = -1;
	while (++i < map->total)
	{
		ret = process_line(map, all_lines, &map_lines, i);
		if (ret == -1)
			return (free(map_lines), -1);
		if (ret == 1)
			break ;
	}
	*mlo = map_lines;
	return (map->map_count);
}

/*
 Runs collect, validates headers, builds grid and validates map.
 Frees temporary buffers on failure; keeps map->grid on success.
*/
static int	do_parse(t_map *map, char **all_lines)
{
	char	**map_lines;
	int		map_count;

	map_lines = NULL;
	map_count = collect_lines(map, all_lines, &map_lines);
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
	game->map.total = total;
	return (do_parse(&game->map, all_lines));
}
