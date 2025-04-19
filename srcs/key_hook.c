/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:31:09 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 09:53:26 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_close(t_all *all)
{
	destroy_all(all);
	exit(0);
}

int	ft_key_press(int keycode, t_all *all)
{
	if (keycode == ESCAPE)
	{
		destroy_all(all);
		exit(0);
	}
	if (keycode == 'w')
		all->player->walk_direction = MOVE_FRONT;
	if (keycode == 'd')
		all->player->walk_direction = MOVE_RIGHT;
	if (keycode == 's')
		all->player->walk_direction = MOVE_BACK;
	if (keycode == 'a')
		all->player->walk_direction = MOVE_LEFT;
	if (keycode == RIGHT_ARROW)
		all->player->turn_direction = TURN_RIGHT;
	if (keycode == LEFT_ARROW)
		all->player->turn_direction = TURN_LEFT;
	return (0);
}

int	ft_key_release(int keycode, t_all *all)
{
	if (keycode == 'w' || keycode == 'd' || keycode == 's' || keycode == 'a')
		all->player->walk_direction = 0;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
	{
		all->player->turn_direction = 0;
	}
	return (0);
}
