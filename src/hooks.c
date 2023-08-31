/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:12:29 by sawang            #+#    #+#             */
/*   Updated: 2023/08/30 17:25:11 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "hook.h"
#include "render.h"

void	hook(t_cub *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		quit(data, RENDER_SUCCESS);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		render(data->g_img_full, data, MLX_KEY_W);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		render(data->g_img_full, data, MLX_KEY_S);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		render(data->g_img_full, data, MLX_KEY_A);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		render(data->g_img_full, data, MLX_KEY_D);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		render(data->g_img_full, data, MLX_KEY_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		render(data->g_img_full, data, MLX_KEY_LEFT);
}
