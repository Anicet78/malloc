/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:42:51 by agruet            #+#    #+#             */
/*   Updated: 2025/02/28 11:29:16 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (!lst)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_dlstlast(*lst);
		new->prev = last;
		last->next = new;
	}
}
