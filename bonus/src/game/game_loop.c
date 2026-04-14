/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:25:10 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:25:11 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Called by MLX42 once per frame.
** Processes input first, then re-renders the scene and overlays.
*/
void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	update_doors(game);
	render_frame(game);
	draw_minimap(game);
	draw_player_info(game);
}
