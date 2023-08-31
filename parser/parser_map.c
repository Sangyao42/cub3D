/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:15:48 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:56:29 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_rectangle_map(t_parser_data *parser_data, t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_data->map = (char **) ft_calloc(map_data->height + 1, sizeof(char *));
	if (map_data->map == NULL)
		error_handler(parser_data, map_data, PARSER_MALLOC_ERROR);
	while (i < map_data->height)
	{
		map_data->map[i] = \
		(char *) ft_calloc(map_data->width + 1, sizeof(char));
		if (map_data->map[i] == NULL)
			error_handler(parser_data, map_data, PARSER_MALLOC_ERROR);
		ft_memset((void *) map_data->map[i], ' ', map_data->width + 1);
		map_data->map[i][map_data->width] = '\0';
		j = 0;
		while (parser_data->tmp_map[i][j] != '\0')
		{
			map_data->map[i][j] = parser_data->tmp_map[i][j];
			j++;
		}
		i++;
	}
}

t_parser_exit_code	parse_tmp_map(char *line, \
					t_parser_data *parser_data, t_map_data *map_data)
{
	t_parser_exit_code	exit_code;

	while (line)
	{
		if (is_empty_line(line) == true)
			break ;
		exit_code = line_check(line, parser_data);
		if (exit_code != PARSER_SUCCESS)
			return (free(line), exit_code);
		parser_data->tmp_map = \
		extend_string_array(parser_data->tmp_map, map_data->height);
		if (parser_data->tmp_map == NULL)
			return (free(line), PARSER_MALLOC_ERROR);
		parser_data->tmp_map[map_data->height] = cub_strdup(line);
		if (parser_data->tmp_map[map_data->height] == NULL)
			return (free(line), PARSER_MALLOC_ERROR);
		map_data->height++;
		free(line);
		line = get_next_line(parser_data->map_fd);
	}
	return (check_map_parsing_status(line, parser_data));
}

void	parse_map(char *line, t_parser_data *parser_data, t_map_data *map_data)
{
	t_parser_exit_code	exit_code;

	exit_code = parse_tmp_map(line, parser_data, map_data);
	if (exit_code != PARSER_SUCCESS)
		error_handler(parser_data, map_data, exit_code);
	get_max_width_map(parser_data->tmp_map, &map_data->width);
	get_rectangle_map(parser_data, map_data);
	check_map_validity(parser_data, map_data);
}
