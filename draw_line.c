/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:44:40 by axbal             #+#    #+#             */
/*   Updated: 2018/06/15 17:42:28 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wolf.h"

void	large_angle(t_dot p2, t_mlx *list, t_util u)
{
	while (u.c_y != p2.y)
	{
		if (u.ratio_s >= u.ratio)
		{
			u.c_x++;
			u.ratio_s -= u.ratio;
		}
		put_pixel(new_dot(u.c_x, u.c_y), list, new_color(146, 244, 66, 0));
		u.ratio_s += 1;
		u.c_y += u.growth;
	}
}

void	sharp_angle(t_dot p2, t_mlx *list, t_util u)
{
	while (u.c_x != p2.x)
	{
		if (u.ratio_s >= u.ratio)
		{
			u.c_y += u.growth;
			u.ratio_s -= u.ratio;
		}
		put_pixel(new_dot(u.c_x, u.c_y), list, new_color(146, 244, 66, 0));
		u.ratio_s += 1;
		u.c_x++;
	}
}

void	vertical_line(t_dot p1, t_dot p2, t_mlx *list)
{
	int		c_y;

	if (p2.y < p1.y)
		ft_swap(&p2.y, &p1.y);
	c_y = p1.y;
	while (c_y != p2.y)
	{
		put_pixel(new_dot(p1.x, c_y), list, new_color(146, 244, 66, 0));
		c_y += 1;
	}
}

void	horizontal_line(t_dot p1, t_dot p2, t_mlx *list)
{
	int		c_x;

	c_x = p1.x;
	while (c_x != p2.x)
	{
		put_pixel(new_dot(c_x, p1.y), list, new_color(146, 244, 66, 0));
		c_x++;
	}
}

void	draw_line(t_dot p1, t_dot p2, t_mlx *list)
{
	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	if (p1.x == p2.x)
		vertical_line(p1, p2, list);
	else if (p1.y == p2.y)
		horizontal_line(p1, p2, list);
	else if (p2.y > p1.y)
	{
		if ((p2.y - p1.y) > (p2.x - p1.x))
			large_angle(p2, list, init_util(p1, p2, 1));
		else
			sharp_angle(p2, list, init_util(p1, p2, 2));
	}
	else if (p2.y < p1.y)
	{
		if ((p1.y - p2.y) > (p2.x - p1.x))
			large_angle(p2, list, init_util(p1, p2, 1));
		else
			sharp_angle(p2, list, init_util(p1, p2, 2));
	}
}
