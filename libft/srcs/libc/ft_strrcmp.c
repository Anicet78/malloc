/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:21:30 by agruet            #+#    #+#             */
/*   Updated: 2025/03/10 17:50:03 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	if ((j < 0 && i >= 0) || (i < 0 && j >= 0))
		return (1);
	while (i >= 0 && j >= 0 && (unsigned char)s1[i] == (unsigned char)s2[j])
	{
		i--;
		j--;
	}
	if (i > j)
		i = j;
	if (i >= 0)
		return (1);
	return (0);
}
