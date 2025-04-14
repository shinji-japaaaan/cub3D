/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/14 20:48:30 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_max_line_width(char **lines, int *width)
{
	int	i;
	int	line_length;
	int	max_width = 0;

	i = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	*width = max_width;
}


static void	count_map_height(char **lines, int start, int *height)
{
	*height = 0;
	while (lines[start])
	{
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

// マップの中身を出力する関数
void	print_map(t_map *map)
{
	int		i;
	int		height;
	char	**grid;

	height = map->height;
	grid = map->grid;
	printf("Map contents:\n");
	for (i = 0; i < height; i++)
	{
		printf("%s\n", grid[i]);
	}
	printf("\n");
}

void	process_lines(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start_index(lines);
	count_map_height(lines, map_start, &map->height);
	if (map->height > MAX_MAP_HEIGHT)
	{
		free_lines(lines);
		print_error_and_exit("Error: Map height exceeds 100 lines\n");
	}
	get_max_line_width(&lines[map_start], &map->width);
	if (map->width > MAX_MAP_WIDTH)
	{
		free_lines(lines);
		print_error_and_exit("Error: Map width exceeds 100 columns\n");
	}
	map->grid = parse_map(lines, map_start, map->height);
	fill_map_with_spaces(map->grid, map->height, map->width);
	// マップの内容を出力
	print_map(map);
	process_textures(lines, map_start, map);
}
