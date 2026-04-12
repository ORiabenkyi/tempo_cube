/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:57:00 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:22:45 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_error(ERR_ARGS);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (parse_file(&game, argv[1]) == -1)
	{
		free_map(&game.map);
		return (1);
	}
	if (init_game(&game) == -1)
	{
		cleanup(&game);
		return (1);
	}
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
