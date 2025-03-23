/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:15:51 by karai             #+#    #+#             */
/*   Updated: 2025/03/22 17:28:01 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double cnv_rad(double angle)
{
	return(angle * M_PI / 180);
}

bool is_out_map(t_all *all, int hit_ij[2])
{
	if (hit_ij[0] < 0 || hit_ij[0] >= all->map->height)
		return (true);
	if (hit_ij[1] < 0 || hit_ij[1] >= all->map->width)
		return (true);
	return (false);
}

bool is_wall(t_all *all, int hit_ij[2])
{
	if (all->map->grid[hit_ij[0]][hit_ij[1]] == '1')
		return (true);
	return (false);
}

double normalize_rad(double x)
{
	if (x > M_2PI)
		x -= M_2PI;
	else if (x < 0)
		x += M_2PI;
	return (x);
}
