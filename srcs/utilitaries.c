/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:48:20 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/25 16:50:51 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_fail(char *str, t_mlx *list)
{
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
	ft_putstr_fd("State: ", 2);
	ft_putstr_fd("Wolf3d is now properly quitting due to an error.\n", 2);
	free_them_all(list);
	exit(0);
}

void			let_mlx_loop(t_mlx *list)
{
	mlx_hook(WIN_PTR, 17, 1L << 17, &window_closed, list);
	mlx_hook(WIN_PTR, 2, 1L << 0, &key_pressed, list);
	mlx_hook(WIN_PTR, 3, 1L << 1, &key_release, list);
	mlx_loop_hook(MLX_PTR, &read_move_tab, list);
	mlx_loop(MLX_PTR);
}

t_mlx			*new_list(void)
{
	t_mlx		*new;

	if (!(new = (t_mlx *)malloc(sizeof(t_mlx) * 1)))
		ft_fail("Error: Could not allocate memory.", NULL);
	new->map = NULL;
	new->move_tab = NULL;
	new->minimap = NULL;
	new->texture_mode = 1;
	return (new);
}

t_level			*new_stage(t_mlx *list)
{
	t_level		*new;

	if (!(new = (t_level *)malloc(sizeof(t_level) * 1)))
		ft_fail("Error: Could not allocate memory.", list);
	new->map_la = 0;
	new->map_ha = 0;
	new->map_nb = 0;
	new->map_name = NULL;
	return (new);
}

t_player		*new_player(t_mlx *list)
{
	t_player	*new;

	if (!(new = (t_player *)malloc(sizeof(t_player) * 1)))
		ft_fail("Error: Could not allocate memory.", list);
	new->x = 5;
	new->y = 5;
	new->a = 0;
	new->eye_x = 0;
	new->eye_y = 0;
	return (new);
}
