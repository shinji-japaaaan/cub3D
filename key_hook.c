/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:31:09 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 00:46:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_close(t_all *all)
{
	// free_all(all); to be implemeted
	exit(0);
}

int	ft_key_press(int keycode, t_all *all)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == 'w')
		all->player->walkDirection = MOVE_FRONT;
	if (keycode == 'd')
		all->player->walkDirection = MOVE_RIGHT;
	if (keycode == 's')
		all->player->walkDirection = MOVE_BACK;
	if (keycode == 'a')
		all->player->walkDirection = MOVE_LEFT;
	if (keycode == RIGHT_ARROW)
		all->player->turnDirection = TURN_RIGHT;
	if (keycode == LEFT_ARROW)
		all->player->turnDirection = TURN_LEFT;
	return (0);
}

int	ft_key_release(int keycode, t_all *all)
{
	if (keycode == 'w' || keycode == 'd' || keycode == 's' || keycode == 'a')
		all->player->walkDirection = 0;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
	{
		all->player->turnDirection = 0;
	}
	return (0);
}
