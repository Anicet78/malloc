/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:45:13 by agruet            #+#    #+#             */
/*   Updated: 2025/03/05 18:16:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lsize;

	i = 0;
	lsize = ft_strlen(little);
	if (lsize == 0)
		return ((char *)big);
	while (big[i] && i + lsize - 1 < len)
	{
		if (ft_strncmp(big + i, little, lsize) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
