/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_shift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:52:00 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 11:39:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_shift_up(t_dlist **lst, t_dlist *node)
{
	dlst_remove_node(lst, node, NULL);
	ft_dlstadd_front(lst, node);
}

void	ft_dlst_shift_down(t_dlist **lst, t_dlist *node)
{
	dlst_remove_node(lst, node, NULL);
	ft_dlstadd_back(lst, node);
}
