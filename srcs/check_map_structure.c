/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:20:59 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	has_space_around(t_map *map, int x, int y)
{
	char	**g;
	int		h;
	int		w;

	g = map->grid;
	h = map->height;
	w = map->width;
	if (x > 0 && g[x - 1][y] == ' ')
		return (1);
	if (x < h - 1 && g[x + 1][y] == ' ')
		return (1);
	if (y > 0 && g[x][y - 1] == ' ')
		return (1);
	if (y < w - 1 && g[x][y + 1] == ' ')
		return (1);
	return (0);
}

static int	check_adjacent_non_wall(t_map *map)
{
	int		i;
	int		j;
	char	**g;
	int		h;
	int		w;

	i = 0;
	g = map->grid;
	h = map->height;
	w = map->width;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (g[i][j] != '1' && g[i][j] != ' ')
			{
				if (has_space_around(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// マップの中身を出力する関数
static void	print_map(t_map *map)
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

int	check_map_structure(t_map *map)
{
	// マップの内容を出力
	print_map(map);
	if (!check_outer_wall(map))
		return (error("Map has invalid characters at the outer walls"));
	if (!check_adjacent_non_wall(map))
		return (error("Map has adjacent non-wall characters with spaces"));
	return (1);
}
