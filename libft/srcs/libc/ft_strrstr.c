/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:45:13 by agruet            #+#    #+#             */
/*   Updated: 2025/05/28 17:28:52 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *big, const char *little)
{
	char	*start;
	char	*chr;
	size_t	lsize;

	lsize = ft_strlen(little);
	chr = ft_strlstr(big, little, lsize);
	if (!chr)
		return (NULL);
	while (chr)
	{
		start = chr;
		chr = ft_strlstr(start + lsize, little, ft_strlen(big));
	}
	return (start);
}
