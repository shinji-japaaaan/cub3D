/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:58:24 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_wall_char(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

static int	check_top_bottom(char **grid, int width, int height)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (!is_valid_wall_char(grid[0][j]))
		{
			printf("Error: Invalid char '%c' at top row, col %d\n", grid[0][j],
				j);
			return (0);
		}
		if (!is_valid_wall_char(grid[height - 1][j]))
		{
			printf("Error: Invalid char '%c' at bottom row, col %d\n",
				grid[height - 1][j], j);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	check_left_right(char **grid, int width, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!is_valid_wall_char(grid[i][0]))
		{
			printf("Error: Invalid char '%c' at left col, row %d\n", grid[i][0],
				i);
			return (0);
		}
		if (!is_valid_wall_char(grid[i][width - 1]))
		{
			printf("Error: Invalid char '%c' at right col, row %d\n",
				grid[i][width - 1], i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_outer_wall(t_map *map)
{
	int		width;
	int		height;
	char	**grid;

	width = map->width;
	height = map->height;
	grid = map->grid;
	if (!check_top_bottom(grid, width, height))
		return (0);
	if (!check_left_right(grid, width, height))
		return (0);
	return (1);
}
