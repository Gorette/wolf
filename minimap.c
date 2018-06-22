/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:11:32 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/21 16:14:40 by axbal            ###   ########.fr       */
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
	draw_fov(list);
}

void		fill_tab(t_mlx *list, int **tab, int posy, int posx)
{
	int		count;
	int		select;

	minimap_table(list);
	count = -1;
	posy = (int)(PLAYER->y) - 9 - 1;
	while (++count < SQ_NB && ++posy < STAGE->map_ha * 2)
	{
		select = -1;
		posx = (int)(PLAYER->x) - 9 - 1;
		while (++select < SQ_NB && ++posx <= STAGE->map_la * 2)
		{
			tab[count][select] = 0;
			if (posy < 0 || posy > STAGE->map_ha || posx < 0
				|| posx > STAGE->map_la)
				tab[count][select] = 2;
			else if (MAP[posy][posx] == '1')
				tab[count][select] = 1;
			else if (posy == floor(PLAYER->y) && posx == floor(PLAYER->x))
				tab[count][select] = 3;
			else if (MAP[posy][posx] == 'E')
				tab[count][select] = 4;
		}
	}
	color_minimap(list, tab);
}

void		minimap_table(t_mlx *list)
{
	int		**tab;
	int		count;
	int		select;

	count = -1;
	if (list->minimap == NULL)
	{
		if (!(tab = malloc(sizeof(int *) * SQ_NB)))
			ft_fail("Error: Unable to allocate memory.", list);
		while (++count < SQ_NB)
		{
			if (!(tab[count] = malloc(sizeof(int) * SQ_NB)))
				ft_fail("Error: Unable to allocate memory.", list);
		}
		list->minimap = tab;
	}
	else
		tab = list->minimap;
	count = -1;
	while (++count < SQ_NB)
	{
		select = -1;
		while (++select < SQ_NB)
			tab[count][select] = 2;
	}
}
