/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:36:12 by eunskim           #+#    #+#             */
/*   Updated: 2023/08/31 14:53:13 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_free(t_parser_data *parser_data)
{
	close(parser_data->map_fd);
	free_p(parser_data->texture_path);
	free_str_arr(parser_data->tmp_map);
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_p(void *p)
{
	if (p)
		free(p);
}
