/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:50:11 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/28 17:06:59 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			init_list2(t_mlx *list)
{
	STAGE = new_stage(list);
	MAXDIST = 40;
	STEP = 0.025;
	PLAYER = new_player(list);
	FOV = 1.0472 / 2;
	SPEED = 0.22;
	list->minimap_h = 100;
	list->minimap_l = 100;
	generate_texture(list);
	SQ_NB = 19;
	SQ_S = 5;
	minimap_table(list);
	IN_MENU = 1;
	MENU_S = 0;
	MENU_MNB = 0;
	init_move_tab(list);
	THREAD_NB = 5;
}

void			init_list(t_mlx *list)
{
	HA = 740;
	LA = 1000;
	if (!(MLX_PTR = mlx_init()))
		ft_fail("Error: Connection failed.", list);
	if (!(WIN_PTR = mlx_new_window(MLX_PTR, LA, HA, "WOLF3D")))
		ft_fail("Error: Unable to create window.", list);
	if (!(IMG_PTR = mlx_new_image(MLX_PTR, LA, HA)))
		ft_fail("Error: Unable to create image.", list);
	if (!(IMG_DATA = mlx_get_data_addr(IMG_PTR, &BPP, &S_L, &END)))
		ft_fail("Error: Unable to access image data.", list);
	if (!(MMAP_PTR = mlx_new_image(MLX_PTR, LA, HA)))
		ft_fail("Error: Unable to create image.", list);
	if (!(MMAP_STR = mlx_get_data_addr(MMAP_PTR, &BPP, &S_L, &END)))
		ft_fail("Error: Unable to access image data.", list);
	if (!(M_IMG = mlx_xpm_file_to_image(MLX_PTR, "./tex/menu.xpm", &LA, &HA)))
		ft_fail("Error: Unable to create image.", list);
	BPP = BPP / 8;
	init_list2(list);
}

void			reload_pic(t_mlx *list)
{
	mlx_clear_window(MLX_PTR, WIN_PTR);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	if (IN_MENU == 0)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, MMAP_PTR, 0, 0);
}

int				main(int argc, char **argv)
{
	t_mlx		*list;

	if (argc && argv)
	{
		list = new_list();
		init_list(list);
		lets_draw_menu(list);
		let_mlx_loop(list);
	}
	return (0);
}
