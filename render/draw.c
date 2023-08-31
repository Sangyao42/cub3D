/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:20:51 by sawang            #+#    #+#             */
/*   Updated: 2023/08/31 16:58:47 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"
#include "raycast.h"

t_type	determine_wall(double ray_dir, int side)
{
	if (side == 0 && ray_dir > 0 && ray_dir < PI)
		return (NORTH);
	else if (side == 0 && ray_dir > PI && ray_dir < 2 * PI)
		return (SOUTH);
	else if (side == 1 && ray_dir > PI / 2 && ray_dir < 3 * PI / 2)
		return (WEST);
	else if (side == 1 && ((ray_dir > 0 && ray_dir < PI / 2) || \
		(ray_dir > 3 * PI / 2 && ray_dir < 2 * PI)))
		return (EAST);
	else
		return (NORTH);
}

// int	determine_tex_x(t_vec intersec, t_type wall_type, \
// 	mlx_texture_t *texture_to_draw)
// {
// 	int	tex_x;

// 	if (wall_type == NORTH)
// 		tex_x = (int)intersec.x % TILE_SIZE;
// 	else if (wall_type == SOUTH)
// 		tex_x = texture_to_draw->width - ((int)intersec.x % TILE_SIZE) - 1;
// 	else if (wall_type == WEST)
// 		tex_x = texture_to_draw->width - ((int)intersec.y % TILE_SIZE) - 1;
// 	else if (wall_type == EAST)
// 		tex_x = (int)intersec.y % TILE_SIZE;
// 	else
// 		tex_x = 0;
// 	// printf("howhowhow tex_x = %d\n", tex_x);
// 	return (tex_x);
// }

int	determine_tex_x(t_vec intersec, t_type wall_type, mlx_texture_t *texture_to_draw)
{
	int	tex_x;

	double x_scale;
	x_scale = texture_to_draw->width / TILE_SIZE;
	if (wall_type == NORTH)
		tex_x = (int)intersec.x % TILE_SIZE * x_scale;
	else if (wall_type == SOUTH)
		tex_x = texture_to_draw->width - ((int)intersec.x % TILE_SIZE * x_scale) - 1;
	else if (wall_type == WEST)
		tex_x = texture_to_draw->width - ((int)intersec.y % TILE_SIZE * x_scale) - 1;
	else if (wall_type == EAST)
		tex_x = (int)intersec.y % TILE_SIZE * x_scale;
	else
		tex_x = 0;
	return (tex_x);
}

int	determine_tex_y(t_ray ray, mlx_texture_t *texture_to_draw, int img_j)
{
	int	tex_y;

	tex_y = (img_j - ray.wall_top) * texture_to_draw->height / ray.wall_height;
	return (tex_y);
}

void	draw_texture(mlx_image_t *g_img, double x, t_ray ray, mlx_texture_t *wall_tex[])
{
	t_type			wall_type;
	mlx_texture_t	*tex_to_draw;
	int				tex_x;
	int				tex_y;
	double			img_j;

	wall_type = determine_wall(ray.ray_dir, ray.side);
	tex_to_draw = wall_tex[wall_type];
	tex_x = determine_tex_x(ray.intersec, wall_type, tex_to_draw);
	img_j = 0;
	while (img_j < HEIGHT)
	{
		//inside determine_tex_y, check if the wall_top < 0 and wall_bottom > HEIGHT
		if (img_j >= ray.wall_top && img_j < ray.wall_bottom)
		{
			tex_y = determine_tex_y(ray, tex_to_draw, img_j);
			// set the image pixel
			g_img->pixels[((uint32_t)img_j * WIDTH + (uint32_t)x) * BPP] = \
				tex_to_draw->pixels[(tex_y * tex_to_draw->width + tex_x) * BPP];
			g_img->pixels[((uint32_t)img_j * WIDTH + (uint32_t)x) * BPP + 1] = \
				tex_to_draw->pixels[(tex_y * tex_to_draw->width + tex_x) * BPP + 1];
			g_img->pixels[((uint32_t)img_j * WIDTH + (uint32_t)x) * BPP + 2] = \
				tex_to_draw->pixels[(tex_y * tex_to_draw->width + tex_x) * BPP + 2];
			g_img->pixels[((uint32_t)img_j * WIDTH + (uint32_t)x) * BPP + 3] = \
				tex_to_draw->pixels[(tex_y * tex_to_draw->width + tex_x) * BPP + 3];
		}
		img_j++;
	}
}

void	draw(mlx_image_t *g_img, t_ray *rays, t_map_data map_data, mlx_texture_t *wall_tex[])
{
	int		i;
	t_vec	ceiling_range;
	t_vec	floor_range;

	i = 0;
	while (i < WIDTH)
	{
		// draw_sky
		ceiling_range.x = 0;
		ceiling_range.y = rays[i].wall_top;
		draw_verti_line(g_img, i, ceiling_range, map_data.ceiling_color);
		// draw_wall
		// draw_verti_line(g_img, i, rays[i].wall_top, rays[i].wall_bottom, 0xF4C2C2FF);
		// draw texture for the walls
		draw_texture(g_img, i, rays[i], wall_tex);
		// draw_floor
		floor_range.x = rays[i].wall_bottom;
		floor_range.y = HEIGHT;
		draw_verti_line(g_img, i, floor_range, map_data.floor_color);
		i++;
	}
}
