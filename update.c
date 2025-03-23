/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:46:46 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 09:35:37 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_WallInside(t_all *all, double x, double y)
{
	int	idx_x;
	int	idx_y;

	idx_x = ceil(x) / TILE_SIZE;
	idx_y = ceil(y) / TILE_SIZE;
	if (idx_x < 1 || idx_x > all->map->width - 1 || idx_y < 1
		|| idx_y > all->map->height - 1)
		return (true);
	if (all->map->grid[idx_y][idx_x] == '1')
		return (true);
	return (false);
}

void	update(t_all *all, t_player *player)
{
	double	moveStep;
	double	newPlayerX;
	double	newPlayerY;

	player->ang += player->turnDirection * player->rotSpeed;
	if (player->walkDirection == MOVE_FRONT)
	{
		newPlayerX = player->px + cos(player->ang) * player->moveSpeed;
		newPlayerY = player->py + sin(player->ang) * player->moveSpeed;
	}
	else if (player->walkDirection == MOVE_BACK)
	{
		newPlayerX = player->px + cos(player->ang) * -1 * player->moveSpeed;
		newPlayerY = player->py + sin(player->ang) * -1 * player->moveSpeed;
	}
	else if (player->walkDirection == MOVE_LEFT)
	{
		newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(90)))
			* player->moveSpeed;
		newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(90)))
			* player->moveSpeed;
	}
	else if (player->walkDirection == MOVE_RIGHT)
	{
		newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(270)))
			* player->moveSpeed;
		newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(270)))
			* player->moveSpeed;
	}
	else
	{
		newPlayerX = player->px;
		newPlayerY = player->py;
	}
	if (!is_WallInside(all, newPlayerX, newPlayerY))
	{
		player->px = newPlayerX;
		player->py = newPlayerY;
	}
}
