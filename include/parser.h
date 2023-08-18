/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:59:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/18 20:19:11 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "cub3D.h"

typedef enum e_parser_exit_code
{
	PARSER_SUCCESS,
	PARSER_MALLOC_ERROR,
	EMPTY_FILE,
	GRAPHIC_DATA_INCOMPLETE,
	INACCESIBLE_TEXTURE,
	BAD_TEXTURE_EXTENSION,
	BAD_TEXTURE_SIZE,
	BAD_RGB,
	NO_MAP_FOUND,
	EMPTY_LINE_IN_MAP,
	INVALID_ELEMENT,
	MULTIPLE_PLAYER,
	UNCLOSED_MAP
}	t_parser_exit_code;

typedef struct s_map_data
{
	mlx_texture_t*	wall_north;
	mlx_texture_t*	wall_west;
	mlx_texture_t*	wall_south;
	mlx_texture_t*	wall_east;
	int32_t			ground_color;
	int32_t			ceiling_color;
	int32_t			map_width;
	int32_t			map_height;
	char			**map;
}	t_map_data;

#endif