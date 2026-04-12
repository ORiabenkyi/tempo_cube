/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:41 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 10:24:44 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

# define CHAR_W   10
# define CHAR_H   20
# define INFO_W   260
# define INFO_IMG_H (INFO_LINES * CHAR_H)

/*
** Converts a double to a compact string: [-]NNN.NN (two decimal places).
*/
static void	dbl_to_buf(double v, char *buf)
{
	int	neg;
	int	ip;
	int	fp;
	int	i;

	neg = (v < 0.0);
	if (neg)
		v = -v;
	ip = (int)v;
	fp = (int)((v - ip) * 100.0 + 0.5);
	if (fp >= 100)
	{
		fp -= 100;
		ip++;
	}
	i = 0;
	if (neg)
		buf[i++] = '-';
	if (ip >= 100)
		buf[i++] = '0' + ip / 100;
	if (ip >= 10)
		buf[i++] = '0' + (ip / 10) % 10;
	buf[i++] = '0' + ip % 10;
	buf[i++] = '.';
	buf[i++] = '0' + fp / 10;
	buf[i++] = '0' + fp % 10;
	buf[i] = '\0';
}

/*
** Builds one info line into buf (max 64 bytes).
**   idx 0 → "pos  x:<val>  y:<val>"
**   idx 1 → "dir  x:<val>  y:<val>"
**   idx 2 → "pln  x:<val>  y:<val>"
*/
static void	build_line(t_player *p, int idx, char *buf)
{
	char	vx[16];
	char	vy[16];
	double	vxd;
	double	vyd;
	char	*label;

	label = "pos";
	vxd = p->pos_x;
	vyd = p->pos_y;
	if (idx == 1)
	{
		label = "dir";
		vxd = p->dir_x;
		vyd = p->dir_y;
	}
	if (idx == 2)
	{
		label = "pln";
		vxd = p->plane_x;
		vyd = p->plane_y;
	}
	dbl_to_buf(vxd, vx);
	dbl_to_buf(vyd, vy);
	ft_strlcpy(buf, label, 64);
	ft_strlcat(buf, "  x:", 64);
	ft_strlcat(buf, vx, 64);
	ft_strlcat(buf, "  y:", 64);
	ft_strlcat(buf, vy, 64);
}

/*
** Draws string str into image img at the given character row.
** Copies glyph pixels from the font atlas using mlx_get_texoffset().
*/
static void	draw_info_line(mlx_image_t *img, const mlx_texture_t *fnt,
							const char *str, int row)
{
	int32_t		toff;
	uint8_t		*dst;
	const uint8_t	*src;
	int			col;
	int			y;

	col = 0;
	while (*str && col * CHAR_W < (int)img->width)
	{
		toff = mlx_get_texoffset(*str);
		if (toff >= 0)
		{
			y = 0;
			while (y < CHAR_H)
			{
				src = fnt->pixels + (y * fnt->width + toff) * 4;
				dst = img->pixels
					+ ((row * CHAR_H + y) * img->width + col * CHAR_W) * 4;
				memcpy(dst, src, CHAR_W * 4);
				y++;
			}
		}
		col++;
		str++;
	}
}

/*
** Called every frame. Updates the persistent info image when show_info is set.
** Creates the image on first call; toggles visibility via enabled flag.
*/
void	draw_player_info(t_game *game)
{
	char				buf[64];
	const mlx_texture_t	*fnt;
	int					i;

	if (!game->show_info)
	{
		if (game->info_img)
			game->info_img->enabled = false;
		return ;
	}
	if (!game->info_img)
	{
		game->info_img = mlx_new_image(game->mlx, INFO_W, INFO_IMG_H);
		if (!game->info_img)
			return ;
		if (mlx_image_to_window(game->mlx, game->info_img, INFO_X, INFO_Y) == -1)
			return ;
	}
	game->info_img->enabled = true;
	memset(game->info_img->pixels, 0, INFO_W * INFO_IMG_H * 4);
	fnt = mlx_get_font();
	i = 0;
	while (i < INFO_LINES)
	{
		build_line(&game->player, i, buf);
		draw_info_line(game->info_img, fnt, buf, i);
		i++;
	}
}
