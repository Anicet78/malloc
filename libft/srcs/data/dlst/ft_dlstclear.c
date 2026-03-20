/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:49:54 by agruet            #+#    #+#             */
/*   Updated: 2025/02/28 12:52:05 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*next;

	if (!lst)
		return ;
	ft_dlst_top(lst);
	while (*lst)
	{
		next = (*lst)->next;
		ft_dlstdelone(*lst, del);
		*lst = next;
	}
}
