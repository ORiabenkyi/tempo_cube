/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:25:13 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 13:12:26 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	cleanup_array(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->tex[i])
		{
			mlx_delete_texture(game->tex[i]);
			game->tex[i] = NULL;
		}
	}
}

/*
 Frees all MLX resources and the parsed map.
*/
void	cleanup(t_game *game)
{
	cleanup_array(game);
	if (game->image && game->mlx)
	{
		mlx_delete_image(game->mlx, game->image);
		game->image = NULL;
	}
	if (game->info_img && game->mlx)
	{
		mlx_delete_image(game->mlx, game->info_img);
		game->info_img = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	free_map(&game->map);
}
