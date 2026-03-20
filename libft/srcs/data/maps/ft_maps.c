/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:34:35 by agruet            #+#    #+#             */
/*   Updated: 2025/03/12 10:58:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_map	*newmap(char *key, char *value)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_map	*ft_maplast(t_map *map)
{
	if (!map)
		return (map);
	while (map->next)
		map = map->next;
	return (map);
}

void	ft_addmap(t_map **map, t_map *new)
{
	if (!map)
		return ;
	if (!(*map))
		(*map) = new;
	else
		ft_maplast(*map)->next = new;
}

void	ft_mapclear(t_map **map)
{
	t_map	*next;

	if (!map)
		return ;
	while (*map)
	{
		next = (*map)->next;
		if ((*map)->key)
			free((*map)->key);
		if ((*map)->value)
			free((*map)->value);
		free(*map);
		*map = next;
	}
}

void	map_remove_node(t_map **map, t_map *node)
{
	t_map	*current;
	t_map	*previous;

	if (!map || !*map || !node)
		return ;
	current = *map;
	previous = *map;
	while (current)
	{
		if (current == node)
		{
			if (current == previous)
				*map = node->next;
			else
				previous->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
