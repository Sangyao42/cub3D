/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_mini.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:41:41 by sawang            #+#    #+#             */
/*   Updated: 2023/08/22 21:28:04 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_MINI_H
# define RAYCAST_MINI_H

# include <math.h>

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef HEIGHT
#  define HEIGHT 480
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

# ifndef PI
#  define PI 3.1415
# endif

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_player
{
	t_vec	pos;
	double	dir; //dir of the player is looking at in radian
	t_vec	pos_modif;
	double	dir_modif;
}				t_player;

typedef struct s_map_size
{
	int	height;
	int	width;
	int	tile_size;
}				t_map_size;


typedef struct s_ray
{
	double	ray_dir;
	t_vec	intersec;
	int		side;
	double	dist;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
}				t_ray;

typedef struct s_data
{
	t_player	player;
	//  t_input	input;
	t_map_size	minimap;
	t_ray		ray[WIDTH];
}				t_data;

#endif
