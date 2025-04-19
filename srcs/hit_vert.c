/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:15:48 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 09:52:57 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_map_vert_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int	bx;
	int	by;

	if (M_ONETWO_PI <= angle && angle < M_THREETWO_PI)
		bx = floor(Ax / TILE_SIZE) - 1;
	else
		bx = floor(Ax / TILE_SIZE);
	by = floor(Ay / TILE_SIZE);
	hit_ij[1] = bx;
	hit_ij[0] = by;
}

void	vert_first_hit(t_all all[1], double angle, double AxAy[2],
		double dxdy[2])
{
	if (M_ONETWO_PI <= angle && angle < M_THREETWO_PI)
	{
		AxAy[0] = (int)all->player->px / TILE_SIZE * TILE_SIZE;
		AxAy[1] = all->player->py - ((AxAy[0] - all->player->px) * tan(angle));
		dxdy[1] = TILE_SIZE * tan(angle);
		dxdy[0] = -TILE_SIZE;
	}
	else
	{
		AxAy[0] = ((int)all->player->px / TILE_SIZE + 1) * TILE_SIZE;
		AxAy[1] = all->player->py - ((AxAy[0] - all->player->px) * tan(angle));
		dxdy[1] = -TILE_SIZE * tan(angle);
		dxdy[0] = TILE_SIZE;
	}
}

double	vert_dist(t_all all[1], double angle)
{
	double	axay[2];
	double	dxdy[2];
	int		hit_ij[2];

	vert_first_hit(all, angle, axay, dxdy);
	get_map_vert_idx(axay[0], axay[1], angle, hit_ij);
	while (is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		axay[0] += dxdy[0];
		axay[1] += dxdy[1];
		get_map_vert_idx(axay[0], axay[1], angle, hit_ij);
	}
	if (is_out_map(all, hit_ij))
		return (-1);
	get_map_vert_idx(axay[0], axay[1], angle, hit_ij);
	return (sqrt(pow((axay[0] - all->player->px), 2) + pow((axay[1]
					- all->player->py), 2)));
}
