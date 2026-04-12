/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:25:05 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:31:33 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Reads the mouse X position each frame, computes the horizontal delta from
** the previous frame, and rotates the player accordingly.
** With MOUSE_DISABLED the cursor is hidden and its virtual position
** accumulates without bounds, giving smooth unlimited panning.
*/
static void	handle_mouse(t_game *game)
{
	int32_t	cur_x;
	int32_t	cur_y;
	int		delta;

	mlx_get_mouse_pos(game->mlx, &cur_x, &cur_y);
	delta = (int)cur_x - game->mouse_x;
	if (delta != 0)
		rotate(game, delta * MOUSE_SENS);
	game->mouse_x = (int)cur_x;
}

/*
** Handles single-press toggles for M (minimap) and I (player info).
*/
static void	handle_toggles(t_game *game)
{
	int	m_down;
	int	i_down;

	m_down = mlx_is_key_down(game->mlx, MLX_KEY_M);
	if (m_down && !game->key_m_prev)
		game->show_minimap = !game->show_minimap;
	game->key_m_prev = m_down;
	i_down = mlx_is_key_down(game->mlx, MLX_KEY_I);
	if (i_down && !game->key_i_prev)
		game->show_info = !game->show_info;
	game->key_i_prev = i_down;
}

/*
W / ↑          → move forward
S / ↓          → move backward
A              → strafe left
D              → strafe right
← / →          → rotate left / right
E              → interact with door (single press, not hold)
M              → toggle minimap
I              → toggle player info overlay
ESC            → close window
Mouse X        → rotate left / right
*/
void	handle_keys(t_game *game)
{
	mlx_t	*mlx;
	int		e_down;

	mlx = game->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		move_forward(game, MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_forward(game, -MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		strafe(game, MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		strafe(game, -MOVE_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(game, -ROT_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(game, ROT_SPEED);
	handle_mouse(game);
	e_down = mlx_is_key_down(mlx, MLX_KEY_E);
	if (e_down && !game->key_e_prev)
		interact_door(game);
	game->key_e_prev = e_down;
	handle_toggles(game);
}
