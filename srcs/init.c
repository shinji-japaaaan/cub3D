/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 16:54:44 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**init_lines(int *capacity)
{
	char	**lines;

	*capacity = 20;
	lines = (char **)malloc(sizeof(char *) * (*capacity));
	if (!lines)
		print_perror_and_exit("malloc failed in init_lines\n");
	return (lines);
}

void	init_map(t_map *map)
{
	ft_memset(map, 0, sizeof(t_map));
	map->floor_color = -1;
	map->ceil_color = -1;
}

void	init_flags(t_flags *f)
{
	ft_memset(f, 0, sizeof(t_flags));
}
