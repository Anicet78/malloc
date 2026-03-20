/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:27:24 by tgallet           #+#    #+#             */
/*   Updated: 2026/03/20 19:03:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_chunk	*region_create(size_t capacity)
{
	t_chunk	*region;

	region = (t_chunk *) malloc(sizeof(t_chunk) + capacity * sizeof(uintptr_t));
	if (region == NULL)
		return (NULL);
	region->next = NULL;
	region->count = 0;
	region->capacity = capacity;
	return (region);
}

t_arena	*arena_init(size_t size)
{
	t_arena	*arena;

	if (size <= 0)
		return (NULL);
	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->size = size;
	arena->begin = region_create(size);
	arena->end = arena->begin;
	return (arena);
}

void	*arena_regions_free(t_arena *arena)
{
	t_chunk	*region;
	t_chunk	*next;

	if (!arena)
		return (NULL);
	region = arena->begin;
	while (region != NULL)
	{
		next = region->next;
		free(region);
		region = next;
	}
	arena->begin = NULL;
	arena->end = NULL;
	return (NULL);
}

void	*arena_alloc(size_t size, t_arena *arena)
{
	size_t	capacity;
	t_chunk	*new_chunk;
	void	*res;

	if (!arena || !arena->end || !arena->begin)
		return (NULL);
	size = (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);
	if (arena->end->count + size > arena->end->capacity)
	{
		capacity = arena->size;
		if (capacity < size)
			capacity = size;
		new_chunk = region_create(capacity);
		if (new_chunk == NULL)
			return (arena_regions_free(arena));
		arena->end->next = new_chunk;
		arena->end = new_chunk;
	}
	res = (void *)(arena->end->data + arena->end->count);
	arena->end->count += size;
	return (res);
}

void	*arena_calloc(t_arena *arena, size_t size)
{
	void	*res;

	res = arena_alloc(size, arena);
	if (!res)
		return (NULL);
	ft_memset(res, 0, size);
	return (res);
}
