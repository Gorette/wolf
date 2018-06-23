/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:46:58 by ceugene           #+#    #+#             */
/*   Updated: 2018/05/26 14:42:40 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	map_alloc(t_mlx *list)
{
	int		select;

	select = 0;
	if (MAP)
	{
		free(STAGE->map_name);
		while (select <= STAGE->map_ha + 1)
		{
			free(MAP[select]);
			MAP[select] = NULL;
			select++;
		}
		free(MAP);
		MAP = NULL;
	}
	if (!(MAP = (char **)malloc(sizeof(char*) * 2048)))
		ft_fail("Error: Couldn't allocate memory.", list);
}

int		name_gen(t_mlx *list)
{
	char	*str;
	char	*str2;

	STAGE->map_name = NULL;
	if (!(str = (char *)malloc(sizeof(char) * 12)))
		ft_fail("Error: Couldn't allocate memory.", list);
	ft_strcpy(str, "./maps/map");
	str2 = ft_itoa(STAGE->map_nb);
	str = ft_strcat(str, str2);
	free(str2);
	STAGE->map_name = str;
	FD = open(STAGE->map_name, O_RDONLY);
	if (FD < 0 && STAGE->map_nb == 0)
	{
		ft_putstr_fd("Error: No file '", 2);
		ft_putstr_fd(STAGE->map_name, 2);
		ft_fail("' found. Need map0 to start the game.", list);
	}
	else if (FD < 0)
		return (-1);
	return (0);
}

void	map_checking2(t_mlx *list, int line)
{
	int		s2;
	int		levier;

	s2 = 0;
	levier = 0;
	if (line == 0 || MAP[line + 1][0] == '\0')
		levier = 1;
	if (MAP[line][0] != '1')
		ft_fail("Error: Map must be surrounded by walls.", list);
	if (MAP[line][STAGE->map_la] != '1')
		ft_fail("Error: Map must be surrounded by walls.", list);
	if (levier == 1)
	{
		while (MAP[line][s2])
		{
			if (MAP[line][s2] != '1')
				ft_fail("Error: Map must be surrounded by walls.", list);
			s2++;
		}
	}
}

void	map_checking(t_mlx *list)
{
	int		select;
	int		s2;

	select = 0;
	s2 = 0;
	while (MAP[select][s2])
		s2++;
	STAGE->map_la = s2 - 1;
	select = 0;
	while (MAP[select][0])
	{
		map_checking2(list, select);
		select++;
	}
	STAGE->map_ha = select - 1;
}

void	read_map(t_mlx *list)
{
	int			y_size;
	int			ret;

	y_size = 0;
	map_alloc(list);
	if (name_gen(list) == -1)
		ft_fail("State: No more maps to read. Game over.", list);
	while ((ret = get_next_line(FD, &MAP[y_size])) > 0 && y_size < 2048)
		y_size++;
	if (y_size == 2048 || ret == -1)
		ft_fail("Error: Map is too big or invalid.", list);
	if (y_size <= 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(STAGE->map_name, 2);
		ft_fail(" is an empty file.", list);
	}
	if (y_size < 2)
		ft_fail("Error: Map must be made of several lines.", list);
	map_checking(list);
	place_player(list);
	place_the_player2(list);
}
