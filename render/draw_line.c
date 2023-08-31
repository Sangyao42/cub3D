/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:01:18 by sawang            #+#    #+#             */
/*   Updated: 2023/08/26 16:33:25 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"
#include "raycast.h"

static void	fdf_put_pixel(mlx_image_t *img, t_vec point, uint32_t color)
{
	if (point.x < WIDTH && point.x > 0 && point.y > 0 && point.y < HEIGHT)
		mlx_put_pixel(img, point.x, point.y, color);
}

static void	drawlinelow(mlx_image_t *g_img, t_vec p1, t_vec p2, \
	t_delta delta, uint32_t color)
{
	t_vec	start;

	start = p1;
	delta.yi = 1;
	if (delta.dy < 0)
	{
		delta.yi = -1;
		delta.dy = -delta.dy;
	}
	delta.p = (2 * delta.dy) - delta.dx;
	while (p1.x <= p2.x)
	{
		// p1.color = get_color(p1, start, p2, delta);
		fdf_put_pixel(g_img, p1, color);
		p1.x++;
		if (delta.p < 0)
			delta.p = delta.p + 2 * delta.dy;
		else
		{
			delta.p = delta.p + 2 * delta.dy - 2 * delta.dx;
			p1.y = p1.y + delta.yi;
		}
	}
}

static void	drawlinehigh(mlx_image_t *g_img, t_vec p1, t_vec p2, \
	t_delta delta, uint32_t color)
{
	t_vec	start;

	start = p1;
	delta.xi = 1;
	if (delta.dx < 0)
	{
		delta.xi = -1;
		delta.dx = -delta.dx;
	}
	delta.p = (2 * delta.dx) - delta.dy;
	while (p1.y <= p2.y)
	{
		// p1.color = get_color(p1, start, p2, delta);
		fdf_put_pixel(g_img, p1, color);
		p1.y++;
		if (delta.p < 0)
			delta.p = delta.p + 2 * delta.dx;
		else
		{
			delta.p = delta.p + 2 * delta.dx - 2 * delta.dy;
			p1.x = p1.x + delta.xi;
		}
	}
}

void	draw_line(mlx_image_t *g_img, t_vec p1, t_vec p2, t_delta delta, u_int32_t color)
{
	delta.dx = p2.x - p1.x;
	delta.dy = p2.y - p1.y;
	if (abs(delta.dy) < abs(delta.dx))
	{
		if (p1.x > p2.x)
		{
			delta.dx *= -1;
			delta.dy *= -1;
			drawlinelow(g_img, p2, p1, delta, color);
		}
		else
			drawlinelow(g_img, p1, p2, delta, color);
	}
	else
	{
		if (p1.y > p2.y)
		{
			delta.dx *= -1;
			delta.dy *= -1;
			drawlinehigh(g_img, p2, p1, delta, color);
		}
		else
			drawlinehigh(g_img, p1, p2, delta, color);
	}
}
