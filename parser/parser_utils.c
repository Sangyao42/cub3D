/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:08:20 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/30 18:22:57 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_if_graphic_data_parsed(t_parser_data parser_data, \
		t_map_data *map_data)
{
	if (map_data->wall[NORTH] != NULL && \
	map_data->wall[EAST] != NULL && \
	map_data->wall[SOUTH] != NULL && \
	map_data->wall[WEST] != NULL && \
	parser_data.floor_parsed == true && \
	parser_data.ceiling_parsed == true)
		return (true);
	return (false);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(WHITESPACES, line[i]) != 0)
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

void	open_map_file(const char *path, int *map_fd)
{
	*map_fd = open(path, O_RDONLY);
	if (*map_fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open a file.\n", 2);
		exit(OPEN_ERROR);
	}
}

int	extension_check(const char *path, const char *extension)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	if (path_len < 4)
		return (0);
	if (ft_strncmp(path + path_len - 4, extension, 4) == 0)
		return (1);
	return (0);
}

void	init_data(t_parser_data *parser_data, t_map_data *map_data)
{
	map_data->wall[NORTH] = NULL;
	map_data->wall[EAST] = NULL;
	map_data->wall[SOUTH] = NULL;
	map_data->wall[WEST] = NULL;
	map_data->floor_color = -1;
	map_data->ceiling_color = -1;
	map_data->width = 0;
	map_data->height = 0;
	map_data->map = NULL;
	parser_data->map_fd = 0;
	parser_data->scanner_idx = 0;
	parser_data->texture_path = NULL;
	parser_data->rgb_scanner.red_start = NULL;
	parser_data->rgb_scanner.green_start = NULL;
	parser_data->rgb_scanner.blue_start = NULL;
	parser_data->floor_parsed = false;
	parser_data->ceiling_parsed = false;
	parser_data->player_cnt = 0;
	parser_data->tmp_map = NULL;
}
