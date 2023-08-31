/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:03:21 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:55:52 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int32_t	cub_color_atoi(char *start, int len)
{
	int32_t	sum;

	sum = 0;
	if (start == NULL || len == 0)
		return (-1);
	while (*start >= '0' && *start <= '9' && len)
	{
		sum = sum * 10 + (*start - '0');
		start++;
		len--;
	}
	return (sum);
}

t_parser_exit_code	get_rgb(t_type type, t_rgb *rgb_scanner, \
					t_parser_data *parser_data, t_map_data *map_data)
{
	int32_t		red;
	int32_t		green;
	int32_t		blue;
	uint32_t	color;

	red = cub_color_atoi(rgb_scanner->red_start, rgb_scanner->red_len);
	green = cub_color_atoi(rgb_scanner->green_start, rgb_scanner->green_len);
	blue = cub_color_atoi(rgb_scanner->blue_start, rgb_scanner->blue_len);
	if (red > 255 || red < 0 || green > 255 \
	|| green < 0 || blue > 255 || blue < 0)
		return (BAD_RGB);
	color = ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
	if (type == FLOOR)
	{
		map_data->floor_color = color;
		parser_data->floor_parsed = true;
	}
	else if (type == CEILING)
	{
		map_data->ceiling_color = color;
		parser_data->ceiling_parsed = true;
	}	
	return (PARSER_SUCCESS);
}

t_parser_exit_code	scan_color_code(char *line, int *idx, \
					char **color_start, int *color_len)
{
	*color_len = 0;
	while (line[*idx] && ft_strchr(WHITESPACES, line[*idx]) != 0)
		(*idx)++;
	*color_start = line + *idx;
	while (ft_strchr(WHITESPACES, line[*idx]) == 0 && line[*idx] != ',')
	{
		if (ft_isdigit(line[*idx]) == 0)
			return (BAD_RGB);
		(*idx)++;
	}
	*color_len = (line + *idx - *color_start);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	scan_rgb(char *line, int *idx, t_rgb *rgb_scanner)
{
	t_parser_exit_code	exit_code;

	exit_code = scan_color_code(line, idx, \
	&rgb_scanner->red_start, &rgb_scanner->red_len);
	if (exit_code != PARSER_SUCCESS || line[*idx] != ',')
		return (BAD_RGB);
	(*idx)++;
	exit_code = scan_color_code(line, idx, \
	&rgb_scanner->green_start, &rgb_scanner->green_len);
	if (exit_code != PARSER_SUCCESS || line[*idx] != ',')
		return (BAD_RGB);
	(*idx)++;
	exit_code = scan_color_code(line, idx, \
	&rgb_scanner->blue_start, &rgb_scanner->blue_len);
	if (exit_code != PARSER_SUCCESS)
		return (BAD_RGB);
	if (is_empty_line(line + *idx) == false)
		return (INVALID_DATA);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_rgb(t_type type, char *line, \
					t_parser_data *parser_data, t_map_data *map_data)
{
	t_parser_exit_code	exit_code;

	parser_data->scanner_idx += 1;
	if (type == FLOOR && parser_data->floor_parsed == true)
		return (DATA_AMBIGUITY);
	if (type == CEILING && parser_data->ceiling_parsed == true)
		return (DATA_AMBIGUITY);
	exit_code = scan_rgb(line, \
	&parser_data->scanner_idx, &parser_data->rgb_scanner);
	if (exit_code != PARSER_SUCCESS)
		return (exit_code);
	exit_code = get_rgb(type, &parser_data->rgb_scanner, parser_data, map_data);
	if (exit_code != PARSER_SUCCESS)
		return (exit_code);
	return (PARSER_SUCCESS);
}
