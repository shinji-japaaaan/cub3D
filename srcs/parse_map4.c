/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 16:55:19 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	print_map(t_map *map)
// {
// 	int		i;
// 	int		height;
// 	char	**grid;

// 	height = map->height;
// 	grid = map->grid;
// 	printf("Map contents:\n");
// 	i = 0;
// 	while (i < height)
// 	{
// 		printf("%s\n", grid[i]);
// 		i += 1;
// 	}
// 	printf("\n");
// }

static char	**alloc_map(int height)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	return (map);
}

static void	copy_map_lines(char **dst, char **src, int start, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		dst[i] = ft_strdup(src[start + i]);
		if (!dst[i])
			break ;
		i++;
	}
	if (i != height)
	{
		free_lines(src);
		free_map(dst, i);
		print_error_and_exit("Error: Memory allocation failed\n");
	}
}

static char	**parse_map(char **lines, int start, int height)
{
	char	**map;

	map = alloc_map(height);
	if (!map)
	{
		free_lines(lines);
		print_error_and_exit("Error: Memory allocation failed\n");
	}
	copy_map_lines(map, lines, start, height);
	return (map);
}

static void	parse_and_fill_map(char **lines, t_map *map, int start)
{
	map->grid = parse_map(lines, start, map->height);
	if (!map->grid)
	{
		free_lines(lines);
		print_error_and_exit("Error: Failed to parse map\n");
	}
	if (!fill_map_with_spaces(map->grid, map->height, map->width))
	{
		free_lines(lines);
		free_all(map);
		print_error_and_exit("Error: Failed to fill map with spaces\n");
	}
}

void	process_lines(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start_index(lines);
	count_map_height(lines, map_start, &map->height);
	check_map_height(lines, map->height);
	get_max_line_width(&lines[map_start], &map->width);
	check_map_width(lines, map->width);
	parse_and_fill_map(lines, map, map_start);
	parse_config_lines(lines, map_start, map);
}
