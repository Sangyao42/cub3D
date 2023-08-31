/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:32:22 by sawang            #+#    #+#             */
/*   Updated: 2023/08/29 21:56:13 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycast.h"

#include <stdio.h>

void	cast_ray(t_ray *rays, int worldMap[mapHeight][mapWidth], t_player player, \
	t_map_size map_size)
{
	int		i;
	double	ray_dir;

	i = 0;
	ray_dir = player.dir_modif + FOV / 2 * PI / 180;
	if (ray_dir > 2 * PI)
		ray_dir -= 2 * PI;
	// do I need check the angle after rotate? or just check the angle before rotate?
	// if (ray_dir < 0)
		// ray_dir += 2 * PI;
	//calculate clockwise ray
	while (i < map_size.width)
	{
		rays[i].ray_dir = ray_dir;
		// printf("ray_dir = %f\t", rays[i].ray_dir);
		// printf("ray_dir in degree = %f\t", ray_dir * 180 / PI);
		determine_intersec(&rays[i], worldMap, map_size.tile_size, player);
		// printf("the hit point at the map is [%d][%d]\t", \
		// 	(int)(rays[i].intersec.y / map_size.tile_size), (int)(rays[i].intersec.x / map_size.tile_size));
		// printf("the hit point is (%f, %f)\n", rays[i].intersec.y, rays[i].intersec.x);
		// calculate distance
		rays[i].dist = calc_dist(player.pos_modif.x, rays[i].intersec.x, ray_dir) * cos(player.dir_modif - rays[i].ray_dir);
		// printf("the distance is %f\n", rays[i].dist);
		//calculate wall height
		rays[i].wall_height = map_size.tile_size / rays[i].dist * DIST_TO_PROJ;
		// printf("the wall height is %f\n", rays[i].wall_height);
		rays[i].wall_top = (HEIGHT - rays[i].wall_height) / 2; //screen coordinate
		// printf("the wall top is %f\n", rays[i].wall_top);
		// if (rays[i].wall_top < 0)
		// 	rays[i].wall_top = 0;
		rays[i].wall_bottom = (HEIGHT + rays[i].wall_height) / 2; //screen coordinate
		// printf("the wall bottom is %f\n", rays[i].wall_bottom);
		// if (rays[i].wall_bottom > HEIGHT)
		// 	rays[i].wall_bottom = HEIGHT - 1;
		// draw_line(player.pos_modif, intersec);
		ray_dir -= FOV * PI / 180 / map_size.width;
		if (ray_dir < 0)
			ray_dir += 2 * PI;
		i++;
	}
}

// int	main(void)
// {
// 	t_cub		data;

// 	init_map_size(&(data.map_size));
// 	data.player = get_initial_player_info(worldMap, data.map_size.tile_size);
// 	printf("player_pos.x = %f\n", data.player.pos.x);
// 	printf("player_pos.y = %f\n", data.player.pos.y);
// 	printf("player_dir.x = %f\n", data.player.dir);
// 	printf("player_pos_modified.x = %f\n", data.player.pos_modif.x);
// 	printf("player_pos_modified.y = %f\n", data.player.pos_modif.y);
// 	printf("player_dir_modified = %f\n", data.player.dir_modif);
// 	printf("Below are the intersec points\n");
// 	cast_ray(data.rays, worldMap, data.player, data.map_size);
// }
