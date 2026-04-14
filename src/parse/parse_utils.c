/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:02 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:04 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Frees a NULL-terminated array of strings and the array itself.
*/
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

void	free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free_array(map->grid);
	free(map->doors);
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->grid = NULL;
	map->doors = NULL;
	map->door_count = 0;
}

/*
** Returns 1 if line contains only spaces/tabs (or is empty), 0 otherwise.
** Newlines must already be stripped before calling.
*/
int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

/*
** Returns 1 if every character in line belongs to the map charset:
** 0, 1, N, S, E, W, space, tab.
** An empty line returns 0 (handled separately as empty).
*/
int	is_map_line(char *line)
{
	if (!*line)
		return (0);
	while (*line)
	{
		#if BONUS
		if (!ft_strchr("01DNSEW \t", *line))
		#else
		if (!ft_strchr("01NSEW \t", *line))
		#endif
			return (0);
		line++;
	}
	return (1);
}
