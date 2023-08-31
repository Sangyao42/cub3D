/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:46:31 by sawang            #+#    #+#             */
/*   Updated: 2023/08/30 18:24:56 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"
#include "raycast.h"

t_render_exit_code	wall_texture_load(mlx_texture_t *wall_tex[], char *wall[])
{
	wall_tex[NORTH] = mlx_load_png(wall[NORTH]);
	wall_tex[EAST] = mlx_load_png(wall[EAST]);
	wall_tex[SOUTH] = mlx_load_png(wall[SOUTH]);
	wall_tex[WEST] = mlx_load_png(wall[WEST]);
	if (!wall_tex[NORTH] || !wall_tex[EAST] || \
		!wall_tex[SOUTH] || !wall_tex[WEST])
		return (TEXTURE_CANNOT_LOAD);
	return (RENDER_SUCCESS);
}

t_render_exit_code	wall_is_square(mlx_texture_t *wall_tex[])
{
	if (wall_tex[NORTH]->width != wall_tex[NORTH]->height || \
		wall_tex[EAST]->width != wall_tex[EAST]->height || \
		wall_tex[SOUTH]->width != wall_tex[SOUTH]->height || \
		wall_tex[WEST]->width != wall_tex[WEST]->height)
		return (TEXTURE_NOT_SQUARE);
	return (RENDER_SUCCESS);
}

void	render(mlx_image_t *g_img, t_cub *data, keys_t key)
{
	update_hook_input(data->player, &data->hook_input, key);
	// cub_memset(g_img->pixels, 0, g_img->width * g_img->height * sizeof(int));
	update_player(&data->player, &data->hook_input);
	cast_ray(data->rays, worldMap, data->player, data->map_size);
	draw(g_img, data->rays, data->map_data, data->wall_tex);
}

t_render_exit_code	start_render(t_cub *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub21", true);
	if (!data->mlx)
		return (render_error_print(MLX_CANNOT_INIT));
	if (wall_texture_load(data->wall_tex, data->map_data.wall))
		return (render_error_print(TEXTURE_CANNOT_LOAD));
	if (wall_is_square(data->wall_tex))
		return (render_error_print(TEXTURE_NOT_SQUARE));
	data->g_img_full = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->g_img_full)
		return (render_error_print(IMG_CANNOT_CREATE));
	if (mlx_image_to_window(data->mlx, data->g_img_full, 0, 0))
		return (render_error_print(IMG_CANNOT_DISPLAY));
	render(data->g_img_full, data, 0);
	// mlx_scroll_hook(frame->mlx, (mlx_scrollfunc) scroll_hook, frame);
	// mlx_key_hook(frame->mlx, (mlx_keyfunc) key_hook, frame);
	mlx_loop_hook(data->mlx, (void (*)(void *))hook, data);
	mlx_loop(data->mlx);
	return (RENDER_SUCCESS);
}
