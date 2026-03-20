/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:14:44 by agruet            #+#    #+#             */
/*   Updated: 2025/05/21 16:13:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*arena_realloc(t_arena *arena, void *old_ptr,
			size_t size, size_t old_size)
{
	void	*new_ptr;

	if (!old_ptr || size == 0)
		return (NULL);
	new_ptr = arena_calloc(arena, size);
	if (!new_ptr)
		return (NULL);
	if (size < old_size)
		ft_memmove(new_ptr, old_ptr, size);
	else
		ft_memmove(new_ptr, old_ptr, old_size);
	return (new_ptr);
}

void	clear_arena(t_arena **arena)
{
	arena_regions_free(*arena);
	free(*arena);
	*arena = NULL;
}

void	reset_arena(t_arena **arena)
{
	size_t	size;

	size = (*arena)->size;
	arena_regions_free(*arena);
	free(*arena);
	*arena = arena_init(size);
}
