/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:48:12 by ceugene           #+#    #+#             */
/*   Updated: 2018/05/18 13:54:28 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_texture			xpm_texture(char *name, t_mlx *list)
{
	t_texture		text;

	if (!(text.ptr = mlx_xpm_file_to_image(MLX_PTR, name, &text.width,
		&text.height)))
		ft_fail("Error: Cannot read texture files.", list);
	if (!(text.data = mlx_get_data_addr(text.ptr, &text.bpp, &text.s_l,
		&text.endian)))
		ft_fail("Error: Cannot read texture files.", list);
	text.bpp = text.bpp / 8;
	return (text);
}

void				generate_texture(t_mlx *list)
{
	if (!((list->t) = malloc(sizeof(t_texture) * 6)))
		ft_fail("Error: Unable to allocate memory.", list);
	list->t[0] = xpm_texture("./tex/wall1.xpm", list);
	list->t[1] = xpm_texture("./tex/wall2.xpm", list);
	list->t[2] = xpm_texture("./tex/wall3.xpm", list);
	list->t[3] = xpm_texture("./tex/wall4.xpm", list);
	list->t[4] = xpm_texture("./tex/barrel.xpm", list);
	list->t[5] = xpm_texture("./tex/floor.xpm", list);
}
