/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:46:42 by axbal             #+#    #+#             */
/*   Updated: 2018/06/13 15:28:24 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wolf.h"

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
