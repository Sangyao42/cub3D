/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:03:14 by sawang            #+#    #+#             */
/*   Updated: 2023/08/30 16:38:26 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"
#include "raycast.h"

static void	get_map_data(t_map_data *map_data)
{
	map_data->ceiling_color = 0x89cff0FF;
	map_data->floor_color = 0xD1F3C5FF;
	map_data->wall[0] = "/Users/sawang/Documents/cub3d/walls/oceanN_sq.png";
	map_data->wall[1] = "/Users/sawang/Documents/cub3d/walls/oceanE_sq.png";
	map_data->wall[2] = "/Users/sawang/Documents/cub3d/walls/oceanS_sq.png";
	map_data->wall[3] = "/Users/sawang/Documents/cub3d/walls/oceanW_sq.png";
}

void	init_data(t_cub *data)
{
	get_map_data(&(data->map_data));
	init_map_size(&(data->map_size));
	get_initial_player_info(worldMap, data->map_size.tile_size, \
		&(data->player));
	init_input(&(data->hook_input));
}

int	main(void)
{
	t_cub				data;
	t_render_exit_code	render_exit_code;

	init_data(&data);
	render_exit_code = start_render(&data);
	quit(&data, render_exit_code);
}
