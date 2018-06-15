/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:50:05 by ceugene           #+#    #+#             */
/*   Updated: 2018/05/26 14:40:18 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	next_level(t_mlx *list)
{
	if (IN_MENU == 0)
	{
		close(FD);
		PLAYER->a = 0;
		STAGE->map_nb++;
		read_map(list);
		lets_cast(list);
		image_replacer(list);
	}
}

int		ft_security(t_mlx *list, float x, float y, int key)
{
	float		count;

	count = 0.14;
	while (count <= SPEED)
	{
		if (!(MAP[(int)y][(int)x]) || MAP[(int)y][(int)x] == '1'
			|| MAP[(int)(floor(y))][(int)(floor(x))] == '1')
			return (0);
		if (key == 126)
		{
			x += cos(PLAYER->a) * count;
			y += sin(PLAYER->a) * count;
		}
		else
		{
			x -= cos(PLAYER->a) * count;
			y -= sin(PLAYER->a) * count;
		}
		count += 0.02;
	}
	return (1);
}

void	place_player(t_mlx *list)
{
	int		select;
	int		s2;

	select = 0;
	PLAYER->x = 0;
	PLAYER->y = 0;
	while (MAP[select][0])
	{
		s2 = 0;
		while (MAP[select][s2])
		{
			if (MAP[select][s2] == 'P')
			{
				if (PLAYER->x == 0 && PLAYER->y == 0)
				{
					PLAYER->x = s2;
					PLAYER->y = select;
				}
				else
					ft_fail("Error: Several spawns detected.", list);
			}
			s2++;
		}
		select++;
	}
}

void	free_them_all(t_mlx *list)
{
	if (list)
	{
		close(FD);
		if (WIN_PTR)
		{
			mlx_clear_window(MLX_PTR, WIN_PTR);
			mlx_destroy_window(MLX_PTR, WIN_PTR);
		}
	}
}

void	image_replacer(t_mlx *list)
{
	mlx_clear_window(MLX_PTR, WIN_PTR);
	if (IN_MENU == 0)
		lets_cast(list);
	else if (IN_MENU == 1)
		lets_draw_menu(list);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	if (IN_MENU == 1)
		lets_write(list);
}
