/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:15:55 by sawang            #+#    #+#             */
/*   Updated: 2023/08/29 21:54:56 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"

#include <stdio.h>

t_render_exit_code	render_error_print(t_render_exit_code render_error_code)
{
	ft_putstr_fd("Error\n", 2);
	if (render_error_code == MLX_CANNOT_INIT)
		ft_putstr_fd("cannot init MLX\n", 2);
	else if (render_error_code == TEXTURE_CANNOT_LOAD)
		ft_putstr_fd("cannot load the texture from file\n", 2);
	else if (render_error_code == TEXTURE_NOT_SQUARE)
		ft_putstr_fd("texture is not square\n", 2);
	else if (render_error_code == IMG_CANNOT_CREATE)
		ft_putstr_fd("cannot create image\n", 2);
	else if (render_error_code == IMG_CANNOT_DISPLAY)
		ft_putstr_fd("cannot display image\n", 2);
	else
		ft_putstr_fd("unknown error\n", 2);
	return (render_error_code);
}

void	quit(t_cub *data, t_render_exit_code render_exit_code)
{
	// free_map(data->map_data);//free everything in map_data!!!
	if (data->wall_tex[NORTH])
		mlx_delete_texture(data->wall_tex[NORTH]);
	if (data->wall_tex[EAST])
		mlx_delete_texture(data->wall_tex[EAST]);
	if (data->wall_tex[SOUTH])
		mlx_delete_texture(data->wall_tex[SOUTH]);
	if (data->wall_tex[WEST])
		mlx_delete_texture(data->wall_tex[WEST]);
	if (data->g_img_full)
		mlx_delete_image(data->mlx, data->g_img_full);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (render_exit_code)
		exit (CUB_FAILURE);
	else
		exit (CUB_SUCCESS);
}
