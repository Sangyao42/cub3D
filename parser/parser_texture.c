/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:02:55 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:54:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_exit_code	texture_slicer(char *line, t_parser_data *parser_data)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = parser_data->scanner_idx;
	while (line[start] && ft_strchr(WHITESPACES, line[start]) != 0)
		start++;
	end = start;
	while (ft_strchr(WHITESPACES, line[end]) == 0)
		end++;
	if (end - start < 4)
		return (INVALID_DATA);
	if (is_empty_line(line + end) == false)
		return (INVALID_DATA);
	free_p((void *) parser_data->texture_path);
	parser_data->texture_path = ft_calloc(1, end - start + 1);
	if (parser_data->texture_path == NULL)
		return (PARSER_MALLOC_ERROR);
	while (start + i < end)
	{
		parser_data->texture_path[i] = line[start + i];
		i++;
	}
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_texture(t_type type, char *line, \
					t_parser_data *parser_data, t_map_data *map_data)
{
	t_parser_exit_code	exit_code;
	int					tmp_fd;

	parser_data->scanner_idx += 2;
	exit_code = texture_slicer(line, parser_data);
	if (exit_code != PARSER_SUCCESS)
		return (exit_code);
	if (extension_check(parser_data->texture_path, ".png") == 0)
		return (BAD_TEXTURE_EXTENSION);
	tmp_fd = open(parser_data->texture_path, O_RDONLY);
	if (tmp_fd == -1)
		return (TEXTURE_OPEN_ERROR);
	close(tmp_fd);
	if (map_data->wall[type] != NULL)
		return (DATA_AMBIGUITY);
	map_data->wall[type] = ft_strdup(parser_data->texture_path);
	if (map_data->wall[type] == NULL)
		return (PARSER_MALLOC_ERROR);
	return (PARSER_SUCCESS);
}
