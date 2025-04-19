/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:46:46 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 09:55:07 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_front(t_player *player, double *new_player_x, double *new_player_y)
{
	*new_player_x = player->px + cos(player->ang) * player->move_speed;
	*new_player_y = player->py + sin(player->ang) * -1 * player->move_speed;
}

void	move_back(t_player *player, double *new_player_x, double *new_player_y)
{
	*new_player_x = player->px + cos(player->ang) * -1 * player->move_speed;
	*new_player_y = player->py + sin(player->ang) * player->move_speed;
}

void	move_left(t_player *player, double *new_player_x, double *new_player_y)
{
	*new_player_x = player->px + cos(normalize_rad(player->ang + cnv_rad(90)))
		* player->move_speed;
	*new_player_y = player->py - sin(normalize_rad(player->ang + cnv_rad(90)))
		* player->move_speed;
}

void	move_right(t_player *player, double *new_player_x, double *new_player_y)
{
	*new_player_x = player->px - cos(normalize_rad(player->ang + cnv_rad(90)))
		* player->move_speed;
	*new_player_y = player->py + sin(normalize_rad(player->ang + cnv_rad(90)))
		* player->move_speed;
}

void	update(t_all *all, t_player *player)
{
	double	new_player_x;
	double	new_player_y;

	player->ang += player->turn_direction * player->rot_speed;
	player->ang = normalize_rad(player->ang);
	if (player->walk_direction == MOVE_FRONT)
		move_front(player, &new_player_x, &new_player_y);
	else if (player->walk_direction == MOVE_BACK)
		move_back(player, &new_player_x, &new_player_y);
	else if (player->walk_direction == MOVE_LEFT)
		move_left(player, &new_player_x, &new_player_y);
	else if (player->walk_direction == MOVE_RIGHT)
		move_right(player, &new_player_x, &new_player_y);
	else
	{
		new_player_x = player->px;
		new_player_y = player->py;
	}
	if (!is_wall_inside(all, new_player_x, new_player_y))
	{
		player->px = new_player_x;
		player->py = new_player_y;
	}
}
