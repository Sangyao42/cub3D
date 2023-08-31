/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:34:03 by sawang            #+#    #+#             */
/*   Updated: 2023/08/29 21:53:32 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycast.h"

#include <stdio.h>

t_vec	get_increment_x_intersec(double ray_dir, int tile_size)
{
	t_vec	increment;

	increment.x = tile_size;
	increment.y = tile_size;
	if (ray_dir > 0 && ray_dir < PI)
		increment.y *= -1;
	else if (ray_dir > PI && ray_dir < 2 * PI)
		increment.y *= 1;
	increment.x = (-1) * increment.y / tan(ray_dir);
	return (increment);
}

t_vec	check_horiz_intersec(int worldMap[mapHeight][mapWidth], \
	int tilesize, t_player player, double ray_dir)
{
	t_vec	intersec;
	t_vec	increment;

	intersec.x = INFINITY;
	intersec.y = player.pos_modif.y;
	if (ray_dir == 0 || ray_dir == PI)
		return (intersec);
	if (ray_dir > 0 && ray_dir < PI)
		intersec.y = floor(player.pos_modif.y / tilesize) * tilesize - 0.0001;
	else
		intersec.y = floor(player.pos_modif.y / tilesize) * tilesize + tilesize;
	intersec.x = player.pos_modif.x + (player.pos_modif.y - intersec.y) / \
		tan(ray_dir);
	increment = get_increment_x_intersec(ray_dir, tilesize);
	while ((int)(intersec.y / tilesize) < mapHeight && \
		(int)(intersec.y / tilesize) >= 0 && \
		(int)(intersec.x / tilesize) < mapWidth && \
		(int)(intersec.x / tilesize) >= 0 && \
		worldMap[(int)(intersec.y / tilesize)] \
		[(int)(intersec.x / tilesize)] != 1)
	{
		intersec.x += increment.x;
		intersec.y += increment.y;
	}
	return (intersec);
}

t_vec	get_increment_y_intersec(double ray_dir, int tile_size)
{
	t_vec	increment;

	increment.x = tile_size;
	increment.y = tile_size;
	if (ray_dir > PI / 2 && ray_dir < 3 * PI / 2)
		increment.x *= -1;
	else if ((ray_dir < PI / 2 && ray_dir > 0) || \
		(ray_dir > 3 * PI / 2 && ray_dir < 2 * PI))
		increment.x *= 1;
	increment.y = (-1) * increment.x * tan(ray_dir);
	return (increment);
}

t_vec	check_verti_intersec(int worldMap[mapHeight][mapWidth], \
	int tilesize, t_player player, double ray_dir)
{
	t_vec	intersec;
	t_vec	increment;

	intersec.y = INFINITY;
	intersec.x = player.pos_modif.x;
	if (ray_dir == PI / 2 || ray_dir == 3 * PI / 2)
		return (intersec);
	if (ray_dir > PI / 2 && ray_dir < 3 * PI / 2)
		intersec.x = floor(player.pos_modif.x / tilesize) * tilesize - 0.0001;
	else
		intersec.x = floor(player.pos_modif.x / tilesize) * tilesize + tilesize;
	intersec.y = player.pos_modif.y + (player.pos_modif.x - intersec.x) * \
		tan(ray_dir);
	increment = get_increment_y_intersec(ray_dir, tilesize);
	while ((int)(intersec.y / tilesize) < mapHeight && \
		(int)(intersec.y / tilesize) >= 0 && \
		(int)(intersec.x / tilesize) < mapWidth && \
		(int)(intersec.x / tilesize) >= 0 && \
		worldMap[(int)(intersec.y / tilesize)] \
		[(int)(intersec.x / tilesize)] != 1)
	{
		intersec.x += increment.x;
		intersec.y += increment.y;
	}
	return (intersec);
}

void	determine_intersec(t_ray *ray, int worldMap[mapHeight][mapWidth], \
	int tilesize, t_player player)
{
	t_vec	hor_inters;
	t_vec	ver_inters;

	hor_inters = check_horiz_intersec(worldMap, tilesize, player, ray->ray_dir);
	ver_inters = check_verti_intersec(worldMap, tilesize, player, ray->ray_dir);
	if (hor_inters.x == INFINITY && ver_inters.y == INFINITY)
	{
		ray->intersec.x = INFINITY;
		ray->intersec.y = INFINITY;
	}
	else if (hor_inters.x == INFINITY)
		ray->intersec = ver_inters;
	else if (ver_inters.y == INFINITY)
		ray->intersec = hor_inters;
	else if (calc_dist(player.pos_modif.x, hor_inters.x, ray->ray_dir) < \
		calc_dist(player.pos_modif.x, ver_inters.x, ray->ray_dir))
	{
		ray->side = 0;
		ray->intersec = hor_inters;
	}
	else
	{
		ray->side = 1;
		ray->intersec = ver_inters;
	}
}
