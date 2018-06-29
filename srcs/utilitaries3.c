/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaries3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:30:22 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/29 16:17:37 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			map_searcher(t_mlx *list)
{
	char	*str;
	char	*str2;
	int		fd;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		ft_fail("Error: Couldn't allocate memory.", list);
	ft_strcpy(str, "./maps/map");
	str2 = ft_itoa(MENU_MNB);
	str = ft_strcat(str, str2);
	free(str2);
	fd = open(str, O_RDONLY);
	free(str);
	if (fd < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

void		texture_mode(t_mlx *list)
{
	if (!(IN_MENU))
	{
		if (TEX_ON)
			TEX_ON = 0;
		else
			TEX_ON = 1;
		image_replacer(list);
	}
}

void		*lets_cast2(void *lis)
{
	t_mlx	*list;
	int		x;
	t_point	o;

	list = lis;
	x = list->start;
	o.y = 0;
	o.x = 0;
	while (x < list->limit)
	{
		RAY = (PLAYER->a - FOV / 2) + ((float)x / (float)LA * FOV);
		PLAYER->eye_x = cos(RAY);
		PLAYER->eye_y = sin(RAY);
		lets_search(x, list, o);
		x++;
	}
	pthread_exit(NULL);
}

int			refresh(t_mlx *list)
{
	read_move_tab(list);
	if (IN_MENU == 0)
	{
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, MMAP_PTR, 0, 0);
	}
	return (0);
}
