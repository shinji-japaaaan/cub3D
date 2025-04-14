/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/14 19:26:45 by sishizaw         ###   ########.fr       */
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



int	check_map_structure(t_map *map)
{
	
	if (!check_outer_wall(map))
		return (error("Map has invalid characters at the outer walls"));
	if (!check_adjacent_non_wall(map))
		return (error("Map has adjacent non-wall characters with spaces"));
	return (1);
}
