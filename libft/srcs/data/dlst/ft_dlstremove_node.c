/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:59:15 by agruet            #+#    #+#             */
/*   Updated: 2025/03/14 13:04:29 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_node(t_dlist *node)
{
	if (node->next)
		node->next->prev = node->prev;
	node->prev->next = node->next;
}

void	dlst_remove_node(t_dlist **lst, t_dlist *node, void (*del)(void*))
{
	t_dlist	*current;

	if (!lst || !*lst || !node)
		return ;
	current = *lst;
	while (current)
	{
		if (current == node)
		{
			if (node->prev)
				move_node(node);
			else
			{
				*lst = node->next;
				if (*lst)
					(*lst)->prev = NULL;
			}
			if (del)
				ft_dlstdelone(node, del);
			return ;
		}
		current = current->next;
	}
}
