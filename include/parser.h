/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:59:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 17:06:54 by sawang           ###   ########.fr       */
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
# include <stdbool.h>
# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"

# define WHITESPACES " \t\v\f\r\n"

typedef enum e_parser_exit_code
{
	PARSER_SUCCESS,
	PARSER_MALLOC_ERROR,
	OPEN_ERROR,
	EMPTY_FILE,
	INVALID_DATA,
	BAD_TEXTURE_EXTENSION,
	TEXTURE_OPEN_ERROR,
	DATA_AMBIGUITY,
	BAD_RGB,
	GRAPHIC_DATA_INCOMPLETE,
	NO_MAP_FOUND,
	INVALID_ELEMENT,
	MULTIPLE_PLAYER,
	UNCLOSED_MAP
}	t_parser_exit_code;

typedef enum e_type
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING,
	ERROR
}	t_type;

typedef struct s_rgb
{
	char	*red_start;
	int		red_len;
	char	*green_start;
	int		green_len;
	char	*blue_start;
	int		blue_len;
}	t_rgb;

typedef struct s_parser_data
{
	int		map_fd;
	int		scanner_idx;
	char	*texture_path;
	t_rgb	rgb_scanner;
	bool	floor_parsed;
	bool	ceiling_parsed;
	int		player_cnt;
	char	**tmp_map;
}	t_parser_data;

typedef struct s_map_data
{
	char		*wall[4];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int32_t		width;
	int32_t		height;
	char		**map;
}	t_map_data;

// parser.c
t_parser_exit_code	parser(t_map_data *map_data, const char *path);
t_type				catch_type(char *line, int *idx);
void				parse_graphic_data(char *line, \
					t_parser_data *parser_data, t_map_data *map_data);
char				*check_parsing_status_and_advance(char *line, \
					t_parser_data *parser_data, t_map_data *map_data);

// parser_texture.c
t_parser_exit_code	parse_texture(t_type type, char *line, \
					t_parser_data *parser_data, t_map_data *map_data);
t_parser_exit_code	texture_slicer(char *line, t_parser_data *parser_data);

// parser_rgb.c
t_parser_exit_code	parse_rgb(t_type type, char *line, \
					t_parser_data *parser_data, t_map_data *map_data);
t_parser_exit_code	scan_rgb(char *line, int *idx, t_rgb *rgb_scanner);
t_parser_exit_code	scan_color_code(char *line, int *idx, \
					char **color_start, int *color_len);
t_parser_exit_code	get_rgb(t_type type, t_rgb *rgb_scanner, \
					t_parser_data *parser_data, t_map_data *map_data);
int32_t				cub_color_atoi(char *start, int len);

// parser_map.c
void				parse_map(char *line, \
					t_parser_data *parser_data, t_map_data *map_data);
t_parser_exit_code	parse_tmp_map(char *line, \
					t_parser_data *parser_data, t_map_data *map_data);
void				get_rectangle_map(t_parser_data *parser_data, \
					t_map_data *map_data);

// parser_map_utils.c
char				*cub_strdup(const char *line);
t_parser_exit_code	line_check(char *line, t_parser_data *parser_data);
char				**extend_string_array(char **param, int line_cnt);
t_parser_exit_code	check_map_parsing_status(char *line, \
					t_parser_data *parser_data);
void				get_max_width_map(char **tmp_map, int *max_width);

// parser_map_validity.c
void				check_map_validity(t_parser_data *parser_data, \
					t_map_data *map_data);
void				check_neighbour(int i, int j, \
					t_parser_data *parser_data, t_map_data *map_data);
void				check_outer_wall(int i, int j, \
					t_parser_data *parser_data, t_map_data *map_data);

// parser_utils.c
void				init_data(t_parser_data *parser_data, t_map_data *map_data);
int					extension_check(const char *path, const char *extension);
void				open_map_file(const char *path, int *map_fd);
bool				is_empty_line(char *line);
bool				check_if_graphic_data_parsed(t_parser_data parser_data, \
					t_map_data *map_data);

// parser_error.c
void				parser_free_before_exit(t_parser_data *parser_data, \
					t_map_data *map_data);
void				error_handler(t_parser_data *parser_data, \
					t_map_data *map_data, t_parser_exit_code error);
void				error_handler_2(t_parser_exit_code error);

// parser_free.c
void				free_p(void *p);
void				free_str_arr(char **arr);
void				parser_free(t_parser_data *parser_data);

#endif
