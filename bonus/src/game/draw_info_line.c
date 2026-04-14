/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:24:41 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 16:27:18 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
** Draws string str into image img at the given character row.
** Copies glyph pixels from the font atlas using mlx_get_texoffset().
*/
static void	draw_info_line(mlx_image_t *img, const mlx_texture_t *fnt,
							const char *str, int row)
{
	int32_t			toff;
	uint8_t			*dst;
	const uint8_t	*src;
	int				col;
	int				y;

	col = -1;
	while (*str && ++col * CHAR_W < (int)img->width)
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
				ft_memcpy(dst, src, CHAR_W * 4);
				y++;
			}
		}
		str++;
	}
}

void	dil(mlx_image_t *i, const mlx_texture_t *f,	const char *s, int r)
{
	draw_info_line(i, f, s, r);
}
