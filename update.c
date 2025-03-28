/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:46:46 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 00:05:43 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(t_player *player, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = player->px + cos(player->ang) * player->moveSpeed;
	*newPlayerY = player->py + sin(player->ang) * -1 * player->moveSpeed;
}

void	move_back(t_player *player, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = player->px + cos(player->ang) * -1 * player->moveSpeed;
	*newPlayerY = player->py + sin(player->ang) * player->moveSpeed;
}

void	move_left(t_player *player, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(90)))
		* player->moveSpeed;
	*newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(90))) *
		-1 * player->moveSpeed;
}

void	move_right(t_player *player, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(90))) *
		-1 * player->moveSpeed;
	*newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(90)))
		* player->moveSpeed;
}

void	update(t_all *all, t_player *player)
{
	double	moveStep;
	double	newPlayerX;
	double	newPlayerY;

	player->ang += player->turnDirection * player->rotSpeed;
	player->ang = normalize_rad(player->ang);
	if (player->walkDirection == MOVE_FRONT)
		move_front(player, &newPlayerX, &newPlayerY);
	else if (player->walkDirection == MOVE_BACK)
		move_back(player, &newPlayerX, &newPlayerY);
	else if (player->walkDirection == MOVE_LEFT)
		move_left(player, &newPlayerX, &newPlayerY);
	else if (player->walkDirection == MOVE_RIGHT)
		move_right(player, &newPlayerX, &newPlayerY);
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
