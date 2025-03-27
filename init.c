/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:22 by karai             #+#    #+#             */
/*   Updated: 2025/03/27 22:57:54 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->px = 135;
	player->py = 75;
	player->ang = cnv_rad(135);
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->moveSpeed = STEP_SPEED;
	player->rotSpeed = STEP_ANGLE * ((double)M_PI / 180);
}

void	init_map(t_map *map)
{
	map->floor_color = 0x00123456;
	map->ceil_color = 0x0089A211;
}
