/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:34:35 by agruet            #+#    #+#             */
/*   Updated: 2025/03/20 16:50:01 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_mapsize(t_map *map)
{
	size_t	size;

	size = 0;
	if (!map)
		return (0);
	while (map)
	{
		size++;
		map = map->next;
	}
	return (size);
}
