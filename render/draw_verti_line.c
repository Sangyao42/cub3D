/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_verti_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:33:48 by sawang            #+#    #+#             */
/*   Updated: 2023/08/29 20:19:52 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"
#include "raycast.h"

static void	put_pixel_improved(mlx_image_t *img, t_vec point, uint32_t color)
{
	if (point.x < WIDTH && point.x >= 0 && point.y >= 0 && point.y < HEIGHT)
		mlx_put_pixel(img, point.x, point.y, color);
}

void	draw_verti_line(mlx_image_t *g_img, double x, t_vec draw_range, \
	u_int32_t color)
{
	t_vec	point;

	point.x = x;
	point.y = draw_range.x;
	while (point.y < draw_range.y)
	{
		if (point.y >= 0 && point.y < HEIGHT)
			put_pixel_improved(g_img, point, color);
		point.y++;
	}
}
