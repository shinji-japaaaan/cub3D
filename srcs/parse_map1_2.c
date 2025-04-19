/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 11:00:20 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	copy_data(void **src, void **dst, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	**custom_realloc(void **ptr, int old_size, int new_size)
{
	void	**new_ptr;

	new_ptr = (void **)malloc(sizeof(void *) * new_size);
	if (!new_ptr)
		return (NULL);
	copy_data(ptr, new_ptr, old_size);
	free(ptr);
	return (new_ptr);
}

static char	**resize_lines(char **lines, int *capacity)
{
	int		new_capacity;
	char	**new_lines;

	new_capacity = (*capacity) * 2;
	new_lines = (char **)custom_realloc((void **)lines, *capacity,
			new_capacity);
	if (new_lines)
		*capacity = new_capacity;
	return (new_lines);
}

char	**handle_resize(char **lines, int *cap, char *line, int fd)
{
	char	**new_lines;

	new_lines = resize_lines(lines, cap);
	if (!new_lines)
	{
		free(line);
		free_lines(lines);
		close(fd);
		return (NULL);
	}
	return (new_lines);
}

int	read_chars(int fd, char *buffer)
{
	int	bytes_read;
	int	i;

	i = 0;
	while (1)
	{
		bytes_read = read(fd, &buffer[i], 1);
		if (bytes_read <= 0)
			break ;
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			buffer[i] = '\0';
			return (1);
		}
		i++;
		if (i >= BUFFER_SIZE - 1)
			break ;
	}
	if (i > 0)
	{
		buffer[i] = '\0';
		return (1);
	}
	return (bytes_read);
}
