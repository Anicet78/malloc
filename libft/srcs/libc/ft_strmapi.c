/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:15:55 by agruet            #+#    #+#             */
/*   Updated: 2024/11/20 17:08:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	map = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!map)
		return (NULL);
	while (*(s + i))
	{
		map[i] = (*f)(i, s[i]);
		i++;
	}
	map[i] = 0;
	return (map);
}
