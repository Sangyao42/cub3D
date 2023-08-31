/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:20:51 by sawang            #+#    #+#             */
/*   Updated: 2023/08/31 20:24:23 by sawang           ###   ########.fr       */
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

int	determine_tex_x(t_vec intersec, t_type wall_type, \
	mlx_texture_t *texture_to_draw)
{
	int		tex_x;
	double	x_scale;

	x_scale = texture_to_draw->width / TILE_SIZE;
	if (wall_type == NORTH)
		tex_x = (int)intersec.x % TILE_SIZE * x_scale;
	else if (wall_type == SOUTH)
		tex_x = texture_to_draw->width - \
		((int)intersec.x % TILE_SIZE * x_scale) - 1;
	else if (wall_type == WEST)
		tex_x = texture_to_draw->width - \
		((int)intersec.y % TILE_SIZE * x_scale) - 1;
	else if (wall_type == EAST)
		tex_x = (int)intersec.y % TILE_SIZE * x_scale;
	else
		tex_x = 0;
	return (tex_x);
}

int	determine_tex_y(t_ray ray, mlx_texture_t *texture_to_draw, \
	unsigned int img_j)
{
	int	tex_y;

	tex_y = (img_j - ray.wall_top) * texture_to_draw->height / ray.wall_height;
	return (tex_y);
}

void	update_img_pixel(mlx_image_t *g_img, t_vec img, t_vec tex, \
	mlx_texture_t *tex_to_draw)
{
	g_img->pixels[((uint32_t)img.y * WIDTH + (uint32_t)img.x) * BPP] = \
		tex_to_draw->pixels[((uint32_t)tex.y * tex_to_draw->width + \
		(uint32_t)tex.x) * BPP];
	g_img->pixels[((uint32_t)img.y * WIDTH + (uint32_t)img.x) * BPP + 1] = \
		tex_to_draw->pixels[((uint32_t)tex.y * tex_to_draw->width + \
		(uint32_t)tex.x) * BPP + 1];
	g_img->pixels[((uint32_t)img.y * WIDTH + (uint32_t)img.x) * BPP + 2] = \
		tex_to_draw->pixels[((uint32_t)tex.y * tex_to_draw->width + \
		(uint32_t)tex.x) * BPP + 2];
	g_img->pixels[((uint32_t)img.y * WIDTH + (uint32_t)img.x) * BPP + 3] = \
		tex_to_draw->pixels[((uint32_t)tex.y * tex_to_draw->width + \
		(uint32_t)tex.x) * BPP + 3];
}

void	draw_texture(mlx_image_t *g_img, double x, t_ray ray, \
	mlx_texture_t *wall_tex[])
{
	t_type			wall_type;
	mlx_texture_t	*tex_to_draw;
	t_vec			tex;
	t_vec			img;

	wall_type = determine_wall(ray.ray_dir, ray.side);
	tex_to_draw = wall_tex[wall_type];
	tex.x = determine_tex_x(ray.intersec, wall_type, tex_to_draw);
	img.x = x;
	img.y = 0;
	while (img.y < HEIGHT)
	{
		if (img.y >= ray.wall_top && img.y < ray.wall_bottom)
		{
			tex.y = determine_tex_y(ray, tex_to_draw, img.y);
			update_img_pixel(g_img, img, tex, tex_to_draw);
		}
		img.y++;
	}
}
