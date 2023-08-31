/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:52:13 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/30 18:17:04 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_max_width_map(char **tmp_map, int *max_width)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (tmp_map[i])
	{
		width = ft_strlen(tmp_map[i]);
		if (width > *max_width)
			*max_width = width;
		i++;
	}
}

t_parser_exit_code	check_map_parsing_status(char *line, \
					t_parser_data *parser_data)
{
	while (line && is_empty_line(line) == true)
	{
		free(line);
		line = get_next_line(parser_data->map_fd);
	}
	if (line)
		return (free(line), INVALID_DATA);
	else if (!line && parser_data->tmp_map == NULL)
		return (NO_MAP_FOUND);
	else
		return (PARSER_SUCCESS);
}

char	**extend_string_array(char **param, int line_cnt)
{
	int		i;
	char	**str_arr;

	i = 0;
	str_arr = (char **) ft_calloc(line_cnt + 2, sizeof(char *));
	while (i < line_cnt)
	{
		*(str_arr + i) = *(param + i);
		i++;
	}
	if (param != NULL)
		free(param);
	return (str_arr);
}

t_parser_exit_code	line_check(char *line, t_parser_data *parser_data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (ft_strchr(" 01", line[i]))
			i++;
		else if (ft_strchr("NESW", line[i]))
		{
			parser_data->player_cnt += 1;
			if (parser_data->player_cnt != 1)
				return (MULTIPLE_PLAYER);
			i++;
		}
		else
			return (INVALID_ELEMENT);
	}
	return (PARSER_SUCCESS);
}

char	*cub_strdup(const char *line)
{
	int		i;
	char	*line_cpy;

	i = 0;
	line_cpy = ft_calloc(1, ft_strlen(line) + 1);
	if (line_cpy == NULL)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
	{
		line_cpy[i] = line[i];
		i++;
	}
	return (line_cpy);
}
