/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:48 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:23:49 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Drains the GNL static buffer by reading until EOF/error.
** Must be called while fd is still open.
*/
static void	gnl_drain(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

/*
** Grows lines array if needed, strips trailing newline, appends line.
** Returns 0 on success, -1 on allocation failure (frees all and drains GNL).
*/
static int	add_line(char ***lines, char *line, int *count, int *cap, int fd)
{
	char	**tmp;
	int		len;

	if (*count >= *cap - 2)
	{
		*cap *= 2;
		tmp = ft_calloc(*cap, sizeof(char *));
		if (!tmp)
		{
			free(line);
			free_array(*lines);
			gnl_drain(fd);
			return (-1);
		}
		ft_memcpy(tmp, *lines, sizeof(char *) * (*count));
		free(*lines);
		*lines = tmp;
	}
	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	(*lines)[(*count)++] = line;
	return (0);
}

/*
** Reads every line from fd into a NULL-terminated char** array.
** Caller must free_array() the result.
*/
char	**read_all_lines(int fd, int *count)
{
	char	**lines;
	char	*line;
	int		cap;

	*count = 0;
	cap = 64;
	lines = ft_calloc(cap, sizeof(char *));
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (add_line(&lines, line, count, &cap, fd) == -1)
			return (NULL);
		line = get_next_line(fd);
	}
	return (lines);
}

/*
** Checks that no non-empty lines remain after the map ends.
** Returns 0 if clean, -1 if stray content is found.
*/
int	check_no_content_after(char **all_lines, int total, int from)
{
	int	j;

	j = from;
	while (j < total)
	{
		if (!is_empty_line(all_lines[j]))
			return (ft_error(ERR_AFTER));
		j++;
	}
	return (0);
}
