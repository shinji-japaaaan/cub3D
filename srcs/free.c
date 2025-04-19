/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:03:55 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 16:38:53 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_map *map)
{
	if (map->tex_no)
		free(map->tex_no);
	if (map->tex_so)
		free(map->tex_so);
	if (map->tex_we)
		free(map->tex_we);
	if (map->tex_ea)
		free(map->tex_ea);
}

void	free_all(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free_textures(map);
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
