/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:49:57 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_texture_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(&path[len - 4], ".xpm", 4) != 0)
		return (0);
	return (1);
}

static int	can_open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	extract_texture_path(char *line, char **out_path)
{
	char	*texture_path;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		printf("Error: Missing texture path");
		return (-1);
	}
	texture_path = ft_strdup(&line[i]);
	if (!texture_path)
	{
		perror("Error: ft_strdup failed");
		return (-1);
	}
	*out_path = texture_path;
	return (0);
}

static int	validate_texture_all(char *path)
{
	if (!is_valid_texture_extension(path))
	{
		printf("Error: Invalid texture file format (expected .xpm)");
		free(path);
		return (-1);
	}
	if (!can_open_file(path))
	{
		perror("Error: Texture file does not exist");
		free(path);
		return (-1);
	}
	return (0);
}

int	parse_texture_safe(char *line, char **out_path)
{
	char	*path;

	if (extract_texture_path(line, &path) == -1)
		return (-1);
	if (validate_texture_all(path) == -1)
		return (-1);
	*out_path = path;
	return (0);
}
