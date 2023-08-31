/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:51:26 by sawang            #+#    #+#             */
/*   Updated: 2023/08/26 20:01:31 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycast.h"

#include <math.h>

double	calc_dist(double pos_x, double intersec_x, double ray_dir)
{
	return (fabs((pos_x - intersec_x) / cos(ray_dir)));
}
