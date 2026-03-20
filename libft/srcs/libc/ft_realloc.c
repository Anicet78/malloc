/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:54:32 by agruet            #+#    #+#             */
/*   Updated: 2025/02/07 12:34:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t size, size_t old_size)
{
	void	*new_ptr;

	if (!old_ptr && size == 0)
		return (NULL);
	if (size == 0)
		return (free(old_ptr), NULL);
	new_ptr = ft_calloc(1, size);
	if (!new_ptr)
	{
		if (old_ptr)
			free(old_ptr);
		return (NULL);
	}
	if (size < old_size)
		ft_memmove(new_ptr, old_ptr, size);
	else
		ft_memmove(new_ptr, old_ptr, old_size);
	if (old_ptr)
		free(old_ptr);
	return (new_ptr);
}
