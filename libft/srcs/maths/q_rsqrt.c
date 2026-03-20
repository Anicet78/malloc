/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_rsqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:51:14 by agruet            #+#    #+#             */
/*   Updated: 2025/05/14 15:18:51 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	q_rsqrt(double number)
{
	long			i;
	double			x2;
	double			y;
	const double	threehalfs = 1.5;

	x2 = number * 0.5;
	y = number;
	i = *(int64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *) &i;
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}
