/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:11:32 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/15 16:46:24 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		color_minimap(t_mlx *list, int **tab)
{
	int		select;
	int		count;

	count = 0;
	while (count < SQ_NB)
	{
		select = 0;
		while (select < SQ_NB)
		{
			color_squares(list, SQ_S * select + 2, SQ_S * count 
			+ 2, tab[count][select]);
			select++;
		}
		count++;
	}
}

void		fill_tab(t_mlx *list, int **tab)
{
	int		posx;
	int		posy;
	int		count;
	int		select;

	count = -1;
	posy = (int)(PLAYER->y) - 9;
	while (++count < SQ_NB)
	{
		select = -1;
		posx = (int)(PLAYER->x) - 9;
		while (++select < SQ_NB)
		{
			if (posy < 0 || posy > STAGE->map_ha || posx < 0 || posx > STAGE->map_la)
				tab[count][select] = 2;
			else if (MAP[posy][posx] == '1')
				tab[count][select] = 1;
			else if (posy == floor(PLAYER->y) && posx == floor(PLAYER->x))
				tab[count][select] = 3;
			else
				tab[count][select] = 0;
			posx++;
		}
		posy++;
	}
	color_minimap(list, tab);
}

void		minimap_table(t_mlx *list)
{
	int		**tab;
	int		count;
	int		select;

	count = -1;
	if (!(tab = malloc(sizeof(int *) * SQ_NB)))
		ft_fail("Error: Unable to allocate memory.", list);
	while (++count < SQ_NB)
	{
		if (!(tab[count] = malloc(sizeof(int) * SQ_NB)))
			ft_fail("Error: Unable to allocate memory.", list);
	}
	count = 0;
	while (count < SQ_NB)
	{
		select = 0;
		while (select < SQ_NB)
		{
			tab[count][select] = 0;
			select++;
		}
		count++;
	}
	list->minimap = tab;
}

void		draw_square(t_mlx *list)
{
	t_dot	d;
	int		x;
	int		y;

	y = 2;
	while (y < list->minimap_h - 2)
	{
		x = 0;
		while (x < list->minimap_l)
		{
			if (x >= 2 && x <= list->minimap_l - 2)
			{
				d = new_dot(x, y);
				put_pixel(d, list, new_color(50, 50, 50, 0));
			}
			x++;
		}
		y++;
	}
	fill_tab(list, list->minimap);
}
