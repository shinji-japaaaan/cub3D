/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:59:17 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*allocate_buffer(void)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		perror("Error: Memory allocation failed for buffer");
	return (buffer);
}

static char	*read_line(int fd)
{
	char	*buffer;
	int		status;

	buffer = allocate_buffer();
	if (!buffer)
		return (NULL);
	status = read_chars(fd, buffer);
	if (status <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

static char	**read_loop(int fd, char **lines, int *cap)
{
	char	*line;
	int		count;

	count = 0;
	line = read_line(fd);
	while (line != NULL)
	{
		if (count >= (*cap) - 1)
		{
			lines = handle_resize(lines, cap, line, fd);
			if (!lines)
				return (NULL);
		}
		lines[count++] = line;
		line = read_line(fd);
	}
	lines[count] = NULL;
	return (lines);
}

static int	open_file(const char *filename)
{
	int	fd;

	if (!filename || ft_strlen(filename) < 4 || ft_strcmp(filename
			+ ft_strlen(filename) - 4, ".cub") != 0)
		print_error_and_exit("Error:Invalid file format (expected .cub)\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_perror_and_exit("Error opening file\n");
	return (fd);
}

char	**read_lines(const char *filename)
{
	int		fd;
	int		cap;
	char	**lines;

	fd = open_file(filename);
	lines = init_lines(&cap);
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	lines = read_loop(fd, lines, &cap);
	close(fd);
	return (lines);
}
