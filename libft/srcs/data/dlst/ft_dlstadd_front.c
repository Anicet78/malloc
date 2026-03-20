/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:34:12 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 11:44:25 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (!lst)
		return ;
	if (*lst)
	{
		(*lst)->prev = new;
		new->next = *lst;
		new->prev = NULL;
	}
	*lst = new;
}
