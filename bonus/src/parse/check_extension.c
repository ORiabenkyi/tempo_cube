/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:23:03 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:23:24 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Checks that path ends with ".cub".
** Returns 0 on success, -1 on error.
*/
int	check_extension(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (ft_error(ERR_EXT));
	return (0);
}
