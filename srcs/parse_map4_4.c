/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:06:14 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	validate_texture_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm", 4) != 0)
	{
		free(path);
		print_error_and_exit("Error: Invalid texture file format (expected .xpm)");
	}
}

static void	validate_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		print_perror_and_exit("Error: Texture file does not exist");
	}
	close(fd);
}

char	*parse_texture(char *line)
{
	char	*texture_path;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		print_error_and_exit("Error: Missing texture path");
	texture_path = ft_strdup(&line[i]);
	if (!texture_path)
		print_perror_and_exit("Error: Missing texture path");
	validate_texture_path(texture_path);
	validate_texture_file(texture_path);
	return (texture_path);
}
