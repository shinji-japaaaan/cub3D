/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:00:30 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 16:40:55 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_all(t_all *all)
{
	if (all->xpm_no->map)
		mlx_destroy_image(all->mlx, all->xpm_no->map);
	if (all->xpm_so->map)
		mlx_destroy_image(all->mlx, all->xpm_so->map);
	if (all->xpm_we->map)
		mlx_destroy_image(all->mlx, all->xpm_we->map);
	if (all->xpm_ea->map)
		mlx_destroy_image(all->mlx, all->xpm_ea->map);
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->mlx_win)
		mlx_destroy_window(all->mlx, all->mlx_win);
	if (all->mlx)
		mlx_destroy_display(all->mlx);
	free(all->mlx);
	free_all(all->map);
}
