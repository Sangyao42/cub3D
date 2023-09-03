/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:42:38 by sawang            #+#    #+#             */
/*   Updated: 2023/09/03 15:56:29 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "hook.h"
#include "render.h"

void	update_hook_input(t_player player, t_input *input, keys_t key)
{
	if (key == MLX_KEY_RIGHT)
		input->angle = -1 * PI / 180;
	if (key == MLX_KEY_LEFT)
		input->angle = 1 * PI / 180;
	if (key == MLX_KEY_W)
	{
		input->hori_delta = cos(player.dir_modif) * STEP;
		input->vert_delta = -sin(player.dir_modif) * STEP;
	}
	if (key == MLX_KEY_S)
	{
		input->hori_delta = -cos(player.dir_modif) * STEP;
		input->vert_delta = sin(player.dir_modif) * STEP;
	}
	if (key == MLX_KEY_A)
	{
		input->hori_delta = -sin(player.dir_modif) * STEP;
		input->vert_delta = -cos(player.dir_modif) * STEP;
	}
	if (key == MLX_KEY_D)
	{
		input->hori_delta = sin(player.dir_modif) * STEP;
		input->vert_delta = cos(player.dir_modif) * STEP;
	}
}

void	update_player(t_player *player, t_input *input, t_map_data map_data)
{
	t_vec	temp_pos;

	player->dir_modif = player->dir_modif + input->angle;
	if (player->dir_modif > 2 * PI)
		player->dir_modif -= 2 * PI;
	if (player->dir_modif < 0)
		player->dir_modif += 2 * PI;
	temp_pos.x = player->pos_modif.x + input->hori_delta;
	temp_pos.y = player->pos_modif.y + input->vert_delta;
	if ((int)(temp_pos.y / TILE_SIZE) < map_data.height && \
		(int)(temp_pos.y / TILE_SIZE) >= 0 && \
		(int)(temp_pos.x / TILE_SIZE) < map_data.width && \
		(int)(temp_pos.x / TILE_SIZE) >= 0 && \
		map_data.map[(int)(temp_pos.y / TILE_SIZE)] \
		[(int)(temp_pos.x / TILE_SIZE)] != '1' && \
		map_data.map[(int)(temp_pos.y / TILE_SIZE)] \
		[(int)(player->pos_modif.x / TILE_SIZE)] != '1' && \
		map_data.map[(int)(player->pos_modif.y / TILE_SIZE)] \
		[(int)(temp_pos.x / TILE_SIZE)] != '1')
	{
		player->pos_modif.x = temp_pos.x;
		player->pos_modif.y = temp_pos.y;
	}
	init_input(input);
}
