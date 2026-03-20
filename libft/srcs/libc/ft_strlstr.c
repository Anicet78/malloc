/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:16:57 by agruet            #+#    #+#             */
/*   Updated: 2025/03/26 11:55:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	bsize;

	i = 0;
	bsize = ft_strlen(big);
	while (big[i] && i + len <= bsize)
	{
		if (ft_strncmp(big + i, little, len) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
