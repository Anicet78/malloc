/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:46:58 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 15:19:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_strjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*fill_result(char *buffer, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (0);
	while (i < end - start)
	{
		result[i] = buffer[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static int	read_file(int fd, char *buffer, int *start)
{
	int	r_val;

	*start = 0;
	r_val = read(fd, buffer, BUFFER_SIZE);
	return (r_val);
}

static int	find_new_line(char *buffer, int end, int r_val)
{
	while (end < r_val && buffer[end] != '\n')
		end++;
	if (end < r_val && buffer[end] == '\n')
		end++;
	return (end);
}

char	*get_next_line(int fd)
{
	char		*result;
	int			start;
	static int	end;
	static char	buffer[BUFFER_SIZE];
	static int	r_val;

	if (fd < 0)
		return ((end = (r_val = 0)), NULL);
	if (end == 0 || end >= r_val)
		r_val = read_file(fd, buffer, &end);
	if (r_val == 0 || r_val == -1)
		return (NULL);
	start = end;
	end = find_new_line(buffer, end, r_val);
	result = fill_result(buffer, start, end);
	while (result && result[ft_strlen(result) - 1] != '\n'
		&& r_val == BUFFER_SIZE)
	{
		r_val = read(fd, buffer, BUFFER_SIZE);
		if (r_val == -1)
			return (free(result), NULL);
		end = find_new_line(buffer, 0, r_val);
		result = free_strjoin(result, fill_result(buffer, 0, end));
	}
	return (result);
}
