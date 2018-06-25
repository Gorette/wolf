/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:45:35 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/25 14:27:50 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	color_the_floor(int x, t_mlx *list, int color_floor)
{
	int			pos;

	while (++color_floor < HA)
	{
		pos = (x * BPP) + (color_floor * S_L);
		if (x < LA && color_floor < HA && x >= 0 && color_floor >= 0)
		{
			IMG_DATA[pos + 0] = (char)300 - color_floor / 3;
			IMG_DATA[pos + 1] = (char)100;
			IMG_DATA[pos + 2] = (char)160;
			IMG_DATA[pos + 3] = (char)280 - color_floor / 4;
		}
	}
}

void	color_sky_and_floor(int x, t_mlx *list)
{
	int		color_sky;
	int		color_floor;
	int		pos;

	color_sky = -1;
	color_floor = FLOOR - 1;
	if (WALLH < HA)
	{
		while (++color_sky <= FLOOR)
		{
			pos = (x * BPP) + (color_sky * S_L);
			if (x < LA && color_sky < HA && x >= 0 && color_sky >= 0)
			{
				IMG_DATA[pos + 0] = (char)250;
				IMG_DATA[pos + 1] = (char)120;
				IMG_DATA[pos + 2] = (char)120;
				IMG_DATA[pos + 3] = (char)((color_sky / 2) % 255);
			}
		}
		color_the_floor(x, list, color_floor);
	}
}

void	ft_draw_wall(t_mlx *list, int i, int x, t_point o)
{
	int		pos;
	int		y;

	y = ROOF;
	while (y++ < FLOOR)
	{
		if (y > ROOF && y < FLOOR)
		{
			pos = (x * BPP) + (y * S_L);
			if (x < LA && y < HA && x >= 0 && y >= 0)
			{
				o.y += WALLR;
				if (o.y > (float)(list->t[i].height))
					o.y = 0;
				att_text_color_to_image(list, i, pos, o);
				if (DIST > 4)
					IMG_DATA[pos + 3] += (char)(0 + ((int)DIST * 4 % 200));
			}
		}
	}
}
