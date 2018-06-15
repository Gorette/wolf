/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:45:47 by ceugene           #+#    #+#             */
/*   Updated: 2018/05/26 14:40:45 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		window_closed(t_mlx *list)
{
	free_them_all(list);
	exit(0);
}

int		key_pressed(int key, t_mlx *list)
{
	if (IN_MENU == 0)
	{
		if (key == 126 || key == 125)
			move_dir(key, list);
		else if (key == 123 || key == 124)
			move_side(key, list);
	}
	else
	{
		if (key == 123 && MENU_S == 1 && MENU_MNB > 0)
			MENU_MNB--;
		else if (key == 124 && MENU_S == 1 && MENU_MNB < 99)
			MENU_MNB++;
		if (key == 125 && MENU_S < 2)
			MENU_S++;
		if (key == 126 && MENU_S > 0)
			MENU_S--;
		if (key == 36)
			choice_selected(list);
		image_replacer(list);
	}
	return (0);
}

int		move_dir(int key, t_mlx *list)
{
	float	x;
	float	y;

	x = PLAYER->x;
	y = PLAYER->y;
	if (ft_security(list, x, y, key) == 0)
		return (-1);
	if (key == 126)
	{
		x += cos(PLAYER->a) * SPEED;
		y += sin(PLAYER->a) * SPEED;
	}
	else if (key == 125)
	{
		x -= cos(PLAYER->a) * SPEED;
		y -= sin(PLAYER->a) * SPEED;
	}
	PLAYER->x = x;
	PLAYER->y = y;
	image_replacer(list);
	return (0);
}

int		move_side(int key, t_mlx *list)
{
	if (key == 123)
		PLAYER->a -= 0.02;
	else if (key == 124)
		PLAYER->a += 0.02;
	if (PLAYER->a >= 6.30 || PLAYER->a <= -6.30)
		PLAYER->a = 0;
	image_replacer(list);
	return (0);
}

int		key_manager(int key, void *list)
{
	if (key == 53 || key == 12)
		window_closed(list);
	if (key == 35)
		next_level(list);
	return (0);
}
