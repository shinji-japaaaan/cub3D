/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:22 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 10:51:43 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_map *map, t_player *player)
{
	int	i;
	int	j;

	player->turn_direction = 0;
	player->walk_direction = 0;
	player->move_speed = STEP_SPEED;
	player->rot_speed = STEP_ANGLE * ((double)M_PI / 180);
	player->px = 135;
	player->py = 75;
	player->ang = cnv_rad(135);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N')
			{
				printf("NNN\n");
				player->px = j * TILE_SIZE + TILE_SIZE / 2;
				player->py = i * TILE_SIZE + TILE_SIZE / 2;
				player->ang = cnv_rad(90);
			}
			j += 1;
		}
		i += 1;
	}
}

// void	init_map(t_map *map)
// {
// 	map->floor_color = 0x00123456;
// 	map->ceil_color = 0x0089A211;
// }
