/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:29:14 by agruet            #+#    #+#             */
/*   Updated: 2024/11/12 16:31:21 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dest);
	if (len >= size)
		return (size + ft_strlen(src));
	while (src[i] && i + len < (size - 1))
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = 0;
	return (len + ft_strlen(src));
}
