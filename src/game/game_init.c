/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:25:13 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 11:19:33 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Sets player direction and camera plane based on spawn character.
** Camera plane length 0.66 gives ~66° FOV.
** Coordinate system: X = east (+), Y = south (+).
**
**   N → dir (0,-1)  plane (0.66, 0)
**   S → dir (0, 1)  plane (-0.66, 0)
**   E → dir (1, 0)  plane (0, 0.66)
**   W → dir (-1, 0) plane (0, -0.66)
*/

static int	load_textures(t_game *game)
{
	game->tex[TEX_NO] = mlx_load_png(game->map.no);
	game->tex[TEX_SO] = mlx_load_png(game->map.so);
	game->tex[TEX_WE] = mlx_load_png(game->map.we);
	game->tex[TEX_EA] = mlx_load_png(game->map.ea);
	if (!game->tex[TEX_NO] || !game->tex[TEX_SO]
		|| !game->tex[TEX_WE] || !game->tex[TEX_EA])
		return (ft_error(ERR_TEX));
	return (0);
}

/*
** Frees all MLX resources and the parsed map.
** NULL-ifies every pointer after release to make double-call safe.
** Order: textures → image → mlx context → map.
** Textures are external resources; mlx_terminate does NOT free them.
** mlx_delete_image must come before mlx_terminate.
*/
void	cleanup(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i])
		{
			mlx_delete_texture(game->tex[i]);
			game->tex[i] = NULL;
		}
		i++;
	}
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

/*
 Creates the MLX window and image, loads textures, positions player.
 Returns 0 on success, -1 on any failure.
 MLX_MOUSE_NORMAL for normal cursor
*/
int	init_game(t_game *game)
{
	int32_t	mx;
	int32_t	my;

	game->mlx = mlx_init(SCREEN_W, SCREEN_H, "cub3D", false);
	if (!game->mlx)
		return (ft_error("MLX init failed"));
	game->image = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (!game->image)
		return (ft_error("MLX image creation failed"));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		return (ft_error("MLX image_to_window failed"));
	if (load_textures(game) == -1)
		return (-1);
	init_player(game);
	game->show_minimap = 0;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(game->mlx, &mx, &my);
	game->mouse_x = (int)mx;
	return (0);
}
