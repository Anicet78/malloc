/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:03:44 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 13:58:21 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	shift_elem_down(char **tab, char *elem)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == elem)
		{
			while (tab[i + 1])
			{
				tab[i] = tab[i + 1];
				i++;
			}
			tab[i] = elem;
			break ;
		}
		i++;
	}
}

void	shift_elem_up(char **tab, char *elem)
{
	size_t	i;

	if (tab[0] == elem)
		return ;
	i = 1;
	while (tab[i])
	{
		if (tab[i] == elem)
		{
			while (i > 0)
			{
				tab[i] = tab[i - 1];
				i--;
			}
			tab[0] = elem;
			break ;
		}
		i++;
	}
}
