/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceugene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:46:06 by ceugene           #+#    #+#             */
/*   Updated: 2018/06/27 15:34:32 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			lets_persp(int x, float dist, t_mlx *list, t_point o)
{
	int			i;

	ROOF = (HA / 2 - LA / dist);
	FLOOR = HA - ROOF;
	WALLH = FLOOR - ROOF;
	o.y = 0;
	if (ROOF > 0 || FLOOR < HA + 1)
		color_sky_and_floor(x, list);
	if (UP == 1)
		i = 0;
	else if (UP == -1)
		i = 1;
	else if (RIGHT == 1)
		i = 2;
	else
		i = 3;
	if (dist < MAXDIST)
	{
		WALLR = (float)(list->t[i].height) / WALLH;
		if (TEX_ON)
			o.x = get_ox(list, dist, i);
		if (ROOF < 0 && TEX_ON)
			o.y = abs(ROOF) * WALLR;
		ft_draw_wall(list, i, x, o);
	}
}

float			get_ox(t_mlx *list, float dist, int i)
{
	float		collision_point;

	if (UP != 0)
		collision_point = (float)(PLAYER->x + PLAYER->eye_x * dist);
	if (RIGHT != 0)
		collision_point = (float)(PLAYER->y + PLAYER->eye_y * dist);
	collision_point -= floor(collision_point);
	return (collision_point * list->t[i].width);
}

void			get_dir(int distx, int disty, float dist, t_mlx *list)
{
	int			dist_x;
	int			dist_y;
	int			right;
	int			up;

	up = 0;
	right = 0;
	dist -= STEP;
	dist_x = (int)(PLAYER->x + PLAYER->eye_x * dist);
	dist_y = (int)(PLAYER->y + PLAYER->eye_y * dist);
	if (dist_y > disty)
		up = 1;
	else if (dist_y < disty)
		up = -1;
	if (dist_x > distx)
		right = 1;
	else if (dist_x < distx)
		right = -1;
	if (right == 0 || up == 0)
	{
		UP = up;
		RIGHT = right;
	}
}

void			lets_search(int x, t_mlx *list, t_point o)
{
	int			distx;
	int			disty;
	float		dist;

	dist = 0;
	while (dist < MAXDIST)
	{
		dist += STEP;
		distx = (float)(PLAYER->x + PLAYER->eye_x * dist);
		disty = (float)(PLAYER->y + PLAYER->eye_y * dist);
		if (distx < 0 || distx > STAGE->map_la || disty < 0
			|| disty > STAGE->map_ha || !(MAP[disty][distx]))
		{
			dist = MAXDIST;
			break ;
		}
		if (MAP[disty][distx] == '1' || MAP[(int)floor(disty)]
			[(int)floor(distx)] == '1')
			break ;
	}
	if (dist < MAXDIST)
		get_dir(distx, disty, dist, list);
	lets_persp(x, dist, list, o);
	DIST = dist;
}


void			lets_cast(t_mlx *list)
{
	pthread_t	thread_tab[THREAD_NB];
	int			calcul;
	int			stamp;

	stamp = THREAD_NB;
	calcul = LA / THREAD_NB;
	list->start = 0;
	list->limit = calcul;
	THREAD_NB -= 1;
	while (THREAD_NB >= 0)
	{
		if (pthread_create(&thread_tab[THREAD_NB], NULL, &lets_cast2, list)
			!= 0)
			ft_fail("Error: Multi-threading failed.", list);
		pthread_join(thread_tab[THREAD_NB], NULL);
		list->start += calcul;
		list->limit += calcul;
		THREAD_NB--;
	}
	THREAD_NB = stamp;
	fill_tab(list, list->minimap, 0, 0);
}
