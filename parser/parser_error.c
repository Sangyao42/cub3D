/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:06:31 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 17:07:17 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_handler_2(t_parser_exit_code error)
{
	if (error == INVALID_ELEMENT)
		ft_putstr_fd("Invalid element contained in the map.\n", 2);
	else if (error == MULTIPLE_PLAYER)
		ft_putstr_fd("Must have only one player.\n", 2);
	else if (error == UNCLOSED_MAP)
		ft_putstr_fd("Map should be surrounded by walls.", 2);
	return ;
}

void	error_handler(t_parser_data *parser_data, \
		t_map_data *map_data, t_parser_exit_code error)
{
	ft_putstr_fd("Error\n", 2);
	parser_free_before_exit(parser_data, map_data);
	if (error == PARSER_MALLOC_ERROR)
		ft_putstr_fd("Malloc failed\n", 2);
	else if (error == EMPTY_FILE)
		ft_putstr_fd("Empty file.\n", 2);
	else if (error == INVALID_DATA)
		ft_putstr_fd("Invalid data.\n", 2);
	else if (error == BAD_TEXTURE_EXTENSION)
		ft_putstr_fd("Expected a .png file.\n", 2);
	else if (error == TEXTURE_OPEN_ERROR)
		ft_putstr_fd("Texture not readable.\n", 2);
	else if (error == DATA_AMBIGUITY)
		ft_putstr_fd("Duplicated information.\n", 2);
	else if (error == BAD_RGB)
		ft_putstr_fd("RGB value incorrect.\n", 2);
	else if (error == GRAPHIC_DATA_INCOMPLETE)
		ft_putstr_fd("Incomplete data.\n", 2);
	else if (error == NO_MAP_FOUND)
		ft_putstr_fd("No map found.\n", 2);
	else
		error_handler_2(error);
	exit(error);
}

void	parser_free_before_exit(t_parser_data *parser_data, \
		t_map_data *map_data)
{
	close(parser_data->map_fd);
	free_p(parser_data->texture_path);
	free_str_arr(parser_data->tmp_map);
	free_p(map_data->wall[NORTH]);
	free_p(map_data->wall[EAST]);
	free_p(map_data->wall[SOUTH]);
	free_p(map_data->wall[WEST]);
	free_str_arr(map_data->map);
}
