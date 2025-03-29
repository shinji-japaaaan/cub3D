/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:40:30 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error_and_exit(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

static char	**parse_map(char **lines, int start, int height)
{
	char	**map;
	int		i;

	// メモリ確保
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		print_error_and_exit("Error: Memory allocation failed\n");
	i = 0;
	// マップをコピー
	while (i < height)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
			print_error_and_exit("Error: Memory allocation failed\n");
		i++;
	}
	map[i] = NULL; // NULL 終端
	return (map);
}

static void	process_map_lines(char *line, int i, int *map_start,
		int *map_height)
{
	if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
		strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
		line[0] == 'F' || line[0] == 'C' || line[0] == '\0')
		return ; // テクスチャや色設定の行は無視
	if (line[0] == '1' || line[0] == '0' || line[0] == 'N' ||
		line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		if (*map_start == 0) // 初回のみ記録
			*map_start = i;
		(*map_height)++;
	}
}

void	process_lines(char **lines, t_map *map)
{
	int i;
	int map_start;
	int map_height;

	i = 0;
	map_start = 0;
	map_height = 0;
	while (lines[i])
	{
		process_texture_lines(lines[i], map);
		process_map_lines(lines[i], i, &map_start, &map_height);
		i++;
	}
	map->grid = parse_map(lines, map_start, map_height);
	map->height = map_height;
	map->width = ft_strlen(map->grid[0]);
}


