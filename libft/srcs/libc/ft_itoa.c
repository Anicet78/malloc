/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:32:33 by agruet            #+#    #+#             */
/*   Updated: 2026/03/20 19:03:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				size;
	int				is_negative;

	nb = n;
	is_negative = 0;
	if (n < 0)
	{
		nb = -n;
		is_negative = 1;
	}
	size = get_size(nb) + is_negative;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (is_negative)
		str[0] = '-';
	str[size] = 0;
	while (--size >= is_negative)
	{
		str[size] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
