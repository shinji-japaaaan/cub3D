/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:17:16 by sishizaw         ###   ########.fr       */
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

t_map *init_map(void)
{
    t_map *map;

    map = malloc(sizeof(t_map));
    if (!map)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    ft_memset(map, 0, sizeof(t_map));
    map->floor_color = -1;
    map->ceil_color = -1;
    return (map);
}

t_game *init_game(t_map *map)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		free_all(map);
		exit_with_error("malloc failed");
	}
	ft_memset(game, 0, sizeof(t_game));
	return (game);
}

void	init_flags(t_flags *f)
{
	ft_memset(f, 0, sizeof(t_flags));
}

