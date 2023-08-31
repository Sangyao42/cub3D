/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:54:49 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 16:53:13 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef WIDTH
#  define WIDTH 1280
# endif

# ifndef HEIGHT
#  define HEIGHT 960
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 128
# endif

# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"
# include "parser.h"
# include "raycast.h"
// # include "render.h"
# include "hook.h"

# include <stdio.h>
# include <stdlib.h>

typedef enum e_cub_exit_code
{
	CUB_SUCCESS,
	CUB_FAILURE,
	CUB_INVALID_ARGUMENT,
	CUB_WRONG_EXTENSION
}	t_cub_exit_code;

typedef struct s_cub
{
	t_map_data		map_data;
	t_map_size		map_size;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*g_img_full;
	mlx_texture_t	*wall_tex[4];
	t_ray			rays[WIDTH];
	t_input			hook_input;
	// img for minimap
	// mlx_image_t	*g_img_mini;
	// t_map_size	minimap_size;
	// img for rays in minimap
}	t_cub;

/**
 * initializations
 */

t_vec	get_player_pos(int i, int j);
double	get_player_dir(int i, int j);
void	get_initial_player_info(int worldMap[mapHeight][mapWidth], \
	int tile_size, t_player *player);
// void	init_minimap_size(t_map_size *minimap_size);
void	init_map_size(t_map_size *map_size);
void	init_input(t_input *input);

//hook function, should it be here?
void	hook(t_cub *data);

#endif
