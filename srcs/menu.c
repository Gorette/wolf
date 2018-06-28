/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:25:15 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/28 17:08:00 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		place_the_player2(t_mlx *list)
{
	PLAYER->x += 0.5;
	PLAYER->y += 0.5;
	if (PLAYER->y < 1 || PLAYER->x <= 1 || PLAYER->y >= STAGE->map_ha
		|| PLAYER->x >= STAGE->map_la
			|| MAP[(int)PLAYER->y][(int)PLAYER->x] == '1')
		ft_fail("Error: Player spawn is invalid.", list);
}

void		choice_selected(t_mlx *list)
{
	if (MENU_S == 0)
	{
		IN_MENU = 0;
		STAGE->map_nb = 0;
		read_map(list);
		image_replacer(list);
	}
	if (MENU_S == 1)
	{
		if (map_searcher(list) > 0)
		{
			STAGE->map_nb = MENU_MNB;
			IN_MENU = 0;
			read_map(list);
			lets_cast(list);
		}
		else
			ft_putchar('\a');
	}
	else if (MENU_S == 2)
		window_closed(list);
}

void		lets_write(t_mlx *list)
{
	char	*map_nb;

	map_nb = ft_itoa(MENU_MNB);
	mlx_string_put(MLX_PTR, WIN_PTR, 190, 300, 0xFFFFFFF, "PLAY\n");
	mlx_string_put(MLX_PTR, WIN_PTR, 190, 390, 0xFFFFFFF, "MAP\n");
	if (MENU_S == 1)
		mlx_string_put(MLX_PTR, WIN_PTR, 255, 390, 0xDDFFFFF,
			"<< ");
	mlx_string_put(MLX_PTR, WIN_PTR, 300, 390, 0xFFFFFFF, map_nb);
	if (MENU_S == 1)
		mlx_string_put(MLX_PTR, WIN_PTR, 330, 390, 0xDDFFFFF,
		" >>");
	mlx_string_put(MLX_PTR, WIN_PTR, 190, 480, 0xFFFFFFF, "QUIT\n");
	free(map_nb);
}

void		lets_highlight(t_mlx *list)
{
	int		i;
	int		j;
	t_dot	d;
	t_color	c;

	ft_memset(MMAP_STR, 255, ((LA - 1) * BPP + (HA - 1) * S_L));
	c = new_color(60, 60, 110, 120);
	i = 0;
	while (i < 250)
	{
		j = 0;
		while (j < 80)
		{
			d = new_dot((150 + i), (280 + (90 * MENU_S) + j));
			put_pixel(d, list, MMAP_STR, c);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, M_IMG, 0, 0);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, MMAP_PTR, 0, 0);
	lets_write(list);
}

void		lets_draw_menu(t_mlx *list)
{
	lets_highlight(list);
}
