/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_equals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:03:27 by agruet            #+#    #+#             */
/*   Updated: 2025/01/27 15:28:37 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_equals(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if ((s1[i] != s2[i]) && (ft_isalpha(s1[i])
				&& (s1[i] != ft_toupper(s2[i])
					&& s1[i] != ft_tolower(s2[i]))))
			return (0);
		i++;
	}
	if (s1[i] || s2[i])
		return (0);
	return (1);
}
