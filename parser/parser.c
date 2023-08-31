/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:57:35 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:53:55 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*check_parsing_status_and_advance(char *line, \
		t_parser_data *parser_data, t_map_data *map_data)
{
	if (check_if_graphic_data_parsed(*parser_data, map_data) == false)
	{
		free(line);
		error_handler(parser_data, map_data, GRAPHIC_DATA_INCOMPLETE);
	}
	while (line && is_empty_line(line) == true)
	{
		free(line);
		line = get_next_line(parser_data->map_fd);
	}
	if (!line)
		error_handler(parser_data, map_data, NO_MAP_FOUND);
	return (line);
}

void	parse_graphic_data(char *line, \
		t_parser_data *parser_data, t_map_data *map_data)
{
	t_type				type;
	t_parser_exit_code	exit_code;

	exit_code = PARSER_SUCCESS;
	type = catch_type(line, &parser_data->scanner_idx);
	if (type >= NORTH && type <= WEST)
		exit_code = parse_texture(type, line, parser_data, map_data);
	else if (type == FLOOR || type == CEILING)
		exit_code = parse_rgb(type, line, parser_data, map_data);
	else
	{
		free(line);
		error_handler(parser_data, map_data, INVALID_DATA);
	}
	if (exit_code != PARSER_SUCCESS)
	{
		free(line);
		error_handler(parser_data, map_data, exit_code);
	}
}

t_type	catch_type(char *line, int *idx)
{
	*idx = 0;
	while (line[*idx] && ft_strchr(WHITESPACES, line[*idx]) != 0)
		(*idx)++;
	if (line[*idx] == 'N' && line[*idx + 1] == 'O')
		return (NORTH);
	else if (line[*idx] == 'E' && line[*idx + 1] == 'A')
		return (EAST);
	else if (line[*idx] == 'S' && line[*idx + 1] == 'O')
		return (SOUTH);
	else if (line[*idx] == 'W' && line[*idx + 1] == 'E')
		return (WEST);
	else if (line[*idx] == 'F')
		return (FLOOR);
	else if (line[*idx] == 'C')
		return (CEILING);
	else
		return (ERROR);
}

t_parser_exit_code	parser(t_map_data *map_data, const char *path)
{
	t_parser_data	parser_data;
	char			*line;

	init_data(&parser_data, map_data);
	open_map_file(path, &parser_data.map_fd);
	line = get_next_line(parser_data.map_fd);
	if (!line)
		error_handler(&parser_data, map_data, EMPTY_FILE);
	while (line && check_if_graphic_data_parsed(parser_data, map_data) != true)
	{
		if (is_empty_line(line) == false)
			parse_graphic_data(line, &parser_data, map_data);
		free(line);
		line = get_next_line(parser_data.map_fd);
	}
	line = check_parsing_status_and_advance(line, &parser_data, map_data);
	parse_map(line, &parser_data, map_data);
	parser_free(&parser_data);
	return (PARSER_SUCCESS);
}
