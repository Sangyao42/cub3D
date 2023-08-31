/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:08:43 by sawang            #+#    #+#             */
/*   Updated: 2023/08/26 19:09:00 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cub3D.h"

void	*cub_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bc;

	bc = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		bc[i] = (unsigned char) c;
		i++;
	}
	return (bc);
}
