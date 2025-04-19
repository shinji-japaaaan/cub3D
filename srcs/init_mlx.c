/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:22 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 12:19:16 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	start_pos(t_map *map, t_player *player, size_t i, size_t j)
{
	if (map->grid[i][j] == 'N')
	{
		player->px = j * TILE_SIZE + TILE_SIZE / 2;
		player->py = i * TILE_SIZE + TILE_SIZE / 2;
		player->ang = cnv_rad(90);
	}
	if (map->grid[i][j] == 'S')
	{
		player->px = j * TILE_SIZE + TILE_SIZE / 2;
		player->py = i * TILE_SIZE + TILE_SIZE / 2;
		player->ang = cnv_rad(270);
	}
	if (map->grid[i][j] == 'E')
	{
		player->px = j * TILE_SIZE + TILE_SIZE / 2;
		player->py = i * TILE_SIZE + TILE_SIZE / 2;
		player->ang = cnv_rad(0);
	}
	if (map->grid[i][j] == 'W')
	{
		player->px = j * TILE_SIZE + TILE_SIZE / 2;
		player->py = i * TILE_SIZE + TILE_SIZE / 2;
		player->ang = cnv_rad(180);
	}
}

void	init_player(t_map *map, t_player *player)
{
	int	i;
	int	j;

	player->turn_direction = 0;
	player->walk_direction = 0;
	player->move_speed = STEP_SPEED;
	player->rot_speed = STEP_ANGLE * ((double)M_PI / 180);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			start_pos(map, player, i, j);
			j += 1;
		}
		i += 1;
	}
}
