/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_validity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:55:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:55:01 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_outer_wall(int i, int j, \
		t_parser_data *parser_data, t_map_data *map_data)
{
	if (map_data->map[i][j] != ' ' && map_data->map[i][j] != '1')
		error_handler(parser_data, map_data, UNCLOSED_MAP);
	return ;
}

void	check_neighbour(int i, int j, \
		t_parser_data *parser_data, t_map_data *map_data)
{
	if (i < 0 || j < 0 || i == map_data->height || j == map_data->width)
		return ;
	if (map_data->map[i][j] != ' ' && map_data->map[i][j] != '1')
		error_handler(parser_data, map_data, UNCLOSED_MAP);
	return ;
}

void	check_map_validity(t_parser_data *parser_data, t_map_data *map_data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map_data->height)
	{
		j = -1;
		while (++j < map_data->width)
		{	
			if (i == 0 || i == map_data->height - 1 \
			|| j == 0 || j == map_data->width - 1)
				check_outer_wall(i, j, parser_data, map_data);
			if (map_data->map[i][j] == ' ')
			{
				check_neighbour(i - 1, j - 1, parser_data, map_data);
				check_neighbour(i - 1, j, parser_data, map_data);
				check_neighbour(i - 1, j + 1, parser_data, map_data);
				check_neighbour(i, j - 1, parser_data, map_data);
				check_neighbour(i, j + 1, parser_data, map_data);
				check_neighbour(i + 1, j - 1, parser_data, map_data);
				check_neighbour(i + 1, j, parser_data, map_data);
				check_neighbour(i + 1, j + 1, parser_data, map_data);
			}
		}
	}
}
