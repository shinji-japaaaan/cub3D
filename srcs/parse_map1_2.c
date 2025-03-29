/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:21:20 by sishizaw         ###   ########.fr       */
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

static int	read_chars(int fd, char *buffer)
{
	int	bytes_read;
	int	i;

	i = 0;
	while ((bytes_read = read(fd, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			buffer[i] = '\0';
			return (1);
		}
		i++;
		if (i >= BUFFER_SIZE - 1)
			break ;
	}
	return (bytes_read);
}

char	*read_line(int fd)
{
	char	*buffer;
	int		status;

	buffer = allocate_buffer();
	if (!buffer)
		return (NULL);
	status = read_chars(fd, buffer);
	if (status == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (status == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
