/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:46:42 by axbal             #+#    #+#             */
/*   Updated: 2018/06/15 17:25:55 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wolf3d.h"

t_dot	new_dot(int x, int y)
{
	t_dot	new;

	new.x = x;
	new.y = y;
	return (new);
}

void	put_pixel(t_dot d, t_mlx *list, t_color c)
{
	if (d.x >= 0 && d.x <= LA && d.y >= 0 && d.y < HA)
	{
		IMG_DATA[(int)((d.x * BPP) + (d.y * S_L) + 0)] = c.b;
		IMG_DATA[(int)((d.x * BPP) + (d.y * S_L) + 1)] = c.g;
		IMG_DATA[(int)((d.x * BPP) + (d.y * S_L) + 2)] = c.r;
		IMG_DATA[(int)((d.x * BPP) + (d.y * S_L) + 3)] = c.a;
	}
}

t_util		init_util(t_dot p1, t_dot p2, int mode)
{
	t_util		u;

	if (mode == 1)
	{
		u.ratio = p2.y < p1.y ? (float)(p1.y - p2.y) / (p2.x - p1.x) :
		(float)(p2.y - p1.y) / (p2.x - p1.x);
	}
	else
	{
		u.ratio = p2.y < p1.y ? (float)(p2.x - p1.x) / (p1.y - p2.y) :
		(float)(p2.x - p1.x) / (p2.y - p1.y);
	}
	u.ratio_s = 1;
	u.c_x = p1.x;
	u.c_y = p1.y;
	u.growth = p2.y < p1.y ? -1 : 1;
	return (u);
}
