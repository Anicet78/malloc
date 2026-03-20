/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:42:53 by agruet            #+#    #+#             */
/*   Updated: 2025/02/28 13:48:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstprint(t_dlist *lst)
{
	int	i;

	i = 0;
	ft_dlst_top(&lst);
	while (lst)
	{
		ft_printf("%d: %s\n", i, lst->content);
		lst = lst->next;
		i++;
	}
}
