/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/11 22:48:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_max_line_width(char **lines)
{
	int	i;
	int	max_width;
	int	line_length;

	max_width = 0;
	i = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	return (max_width);
}

static void	count_map_height(char **lines, int start, int *height)
{
	*height = 0;
	while (lines[start])
	{
		if (lines[start][0] != '\0')
			(*height)++;
		start++;
	}
}

static int	find_map_start_index(char **lines)
{
	int		i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
		{
			i++;
			continue ;
		}
		if (!(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
				line[0] == 'F' || line[0] == 'C'))
			break ;
		i++;
	}
	return (i);
}

void	process_lines(char **lines, t_map *map)
{
	int	map_start;
	int	map_height;
	int	map_width;

	map_start = find_map_start_index(lines);
	count_map_height(lines, map_start, &map_height);
	map->grid = parse_map(lines, map_start, map_height);
	map_width = get_max_line_width(&lines[map_start]);
	fill_map_with_spaces(map->grid, map_height, map_width);
	map->height = map_height;
	map->width = map_width;
	process_textures(lines, map_start, map);
}
