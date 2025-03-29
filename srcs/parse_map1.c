/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:43:56 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int open_file(const char *filename)
{
    if (!filename || ft_strlen(filename) < 4 || ft_strcmp(filename
			+ ft_strlen(filename) - 4, ".cub") != 0)
    {
        printf("Error: Invalid file format (expected .cub file)\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return (fd);
}

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

static char	**init_lines(int *capacity)
{
	char	**lines;

	*capacity = 20;
	lines = (char **)malloc(sizeof(char *) * (*capacity));
	return (lines);
}

char	**read_lines(const char *filename)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;
	int		capacity;
	char	**new_lines;

	fd = open_file(filename);
	lines = init_lines(&capacity);
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	count = 0;
	while ((line = read_line(fd)) != NULL)
	{
		if (count >= capacity - 1)
		{
			new_lines = resize_lines(lines, &capacity);
			if (!new_lines)
			{
				free(line);
				free_lines(lines);
				close(fd);
				return (NULL);
			}
			lines = new_lines;
		}
		lines[count++] = line;
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}
