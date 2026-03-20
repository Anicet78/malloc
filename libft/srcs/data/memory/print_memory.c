/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:27:32 by agruet            #+#    #+#             */
/*   Updated: 2025/04/13 21:01:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_line(char *addr, size_t size)
{
	size_t	i;

	i = size;
	while (i < 16)
	{
		ft_printf("     ");
		i += 2;
	}
	i = 0;
	while (i < size)
	{
		if (ft_isprint(*(addr + i)) && *(addr + i) > 13)
			ft_printf("%c", *(addr + i));
		else
			ft_printf("%c", '.');
		i++;
	}
	ft_printf("\n");
}

void	*ft_print_memory(void *addr, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (addr && i < size)
	{
		ft_printf("%018p: ", addr + i);
		j = 0;
		while (j < 16 && i + j < size)
		{
			if (i + j + 1 >= size)
				ft_printf("%.2lx   ", *(char *)(addr + i + j));
			else
				ft_printf("%.2lx%.2lx ", *(char *)(addr + i + j),
					*(char *)(addr + i + j + 1));
			j += 2;
		}
		print_line((char *)addr + i, j);
		i += 16;
	}
	return (addr);
}

/* int	main(void)
{
	char	a[] = "Bonjour les aminches\t\n\tc\a est fou\ttout\tce
	qu on peut faire avec\t\n\tprint_memory\n\n\n\tlol.lol\n \0";
	ft_print_memory(a, 92);
	return (0);
} */
