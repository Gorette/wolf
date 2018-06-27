/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:18:44 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/27 15:15:55 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		deactivate_key(int key, t_mlx *list)
{
	int		*tab;

	tab = list->move_tab;
	if (key == 126)
		tab[0] = 0;
	if (key == 125)
		tab[1] = 0;
	if (key == 123)
		tab[2] = 0;
	if (key == 124)
		tab[3] = 0;
}

void		activate_key(int key, t_mlx *list)
{
	int		*tab;

	tab = list->move_tab;
	if (key == 126)
		tab[0] = 1;
	if (key == 125)
		tab[1] = 1;
	if (key == 123)
		tab[2] = 1;
	if (key == 124)
		tab[3] = 1;
}

int			read_move_tab(t_mlx *list)
{
	int		*tab;

	tab = list->move_tab;
	if (tab[0] == 1 && tab[1] == 0)
		move_dir(126, list);
	if (tab[1] == 1 && tab[0] == 0)
		move_dir(125, list);
	if (tab[2] == 1 && tab[3] == 0)
		move_side(123, list);
	if (tab[3] == 1 && tab[2] == 0)
		move_side(124, list);
	image_replacer(list);
	return (0);
}

void		init_move_tab(t_mlx *list)
{
	int		*table;

	if (!(table = malloc(sizeof(int) * 4)))
		ft_fail("Error: Unable to allocate memory.", list);
	table[0] = 0;
	table[1] = 0;
	table[2] = 0;
	table[3] = 0;
	list->move_tab = table;
}
