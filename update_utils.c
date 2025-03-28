/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:05:12 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 00:05:36 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_WallInside(t_all *all, double x, double y)
{
	int idx_x;
	int idx_y;

	idx_x = floor(x) / TILE_SIZE;
	idx_y = floor(y) / TILE_SIZE;
	if (idx_x < 1 || idx_x > all->map->width - 1 || idx_y < 1
		|| idx_y > all->map->height - 1)
		return (true);
	if (all->map->grid[idx_y][idx_x] == '1')
		return (true);
	return (false);
}
