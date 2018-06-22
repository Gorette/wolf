/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:45:28 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/21 17:18:43 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_color		new_color(int r, int g, int b, int a)
{
	t_color		new;

	new.r = r;
	new.g = g;
	new.b = b;
	new.a = a;
	return (new);
}

void	attribute_text_color_to_image(t_mlx *list, int i, int pos, t_point o)
{
	if (list->t[i].data[(int)o.x * list->t[i].bpp
		+ (int)o.y * list->t[i].s_l] + 3 < 255)
	{
		IMG_DATA[pos + 0] = (char)list->t[i].data[(int)o.x * list->t[i].bpp
			+ (int)o.y * list->t[i].s_l];
		IMG_DATA[pos + 1] = (char)list->t[i].data[(int)o.x * list->t[i].bpp
			+ (int)o.y * list->t[i].s_l + 1];
		IMG_DATA[pos + 2] = (char)list->t[i].data[(int)o.x * list->t[i].bpp
			+ (int)o.y * list->t[i].s_l + 2];
		IMG_DATA[pos + 3] = (char)(0 + ((int)DIST * 2 % 200) % 255);
	}
}

void	color_squares(t_mlx *list, int startx, int starty, int wall)
{
	int		c;
	int		s;
	int		clr;

	clr = 130;
	if (wall == 1)
		clr = 70;
	if (wall == 2)
		clr = 210;
	c = starty - 1;
	while (++c <= starty + SQ_S)
	{
		s = startx - 1;
		while (++s <= startx + SQ_S)
		{
			put_pixel(new_dot(s, c), list, new_color(clr, clr, clr, 0));
			if (wall == 3)
				put_pixel(new_dot(s, c), list, new_color(200, clr, clr, 0));
			if (wall == 4)
				put_pixel(new_dot(s, c), list, new_color(clr, 200, clr, 0));
		}
	}
}

void	fill_fov(t_mlx *list, int x, int y, t_dot d)
{
	while (++y < 300)
	{
		x = 0;
		while (x < 200)
		{
			while (MMAP_STR[x * BPP + y * S_L + 3] == (char)255)
			{
				x++;
				if (x > 200)
				{
					x = 0;
					y++;
				}
			}
			d.x = x;
			d.y = y;
			while (MMAP_STR[x * BPP + y * S_L + 3] != (char)255
				|| MMAP_STR[(x + 1) * BPP + y * S_L + 3] != (char)255
					|| MMAP_STR[(x + 2) * BPP + y * S_L + 3] != (char)255)
				x++;
			draw_line(d, new_dot(x, y), list);
		}
	}
}

void	draw_fov(t_mlx *list)
{
	double	ray;
	t_dot	d;

	ft_memset(MMAP_STR, 255, (LA * BPP + HA * S_L));
	d = new_dot(49, 49);
	ray = -(FOV / 2);
	while (ray < FOV / 2)
	{
		draw_line(d, new_dot(d.x + (cos(PLAYER->a + ray) * 30),
			d.y + (sin(PLAYER->a + ray) * 30)), list);
		ray += (double)FOV / 64;
	}
	fill_fov(list, 0, -1, d);
}
