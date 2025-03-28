/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:19:37 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 00:13:47 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_horz_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int	Bx;
	int	By;

	if (0 <= angle && angle < M_PI)
		By = floor(Ay / TILE_SIZE) - 1;
	else
		By = floor(Ay / TILE_SIZE);
	Bx = floor(Ax / TILE_SIZE);
	hit_ij[1] = Bx;
	hit_ij[0] = By;
}

void	horz_first_hit(t_all all[1], double angle, double AxAy[2],
		double dxdy[2])
{
	if (0 <= angle && angle < M_PI)
	{
		AxAy[1] = (int)all->player->py / TILE_SIZE * TILE_SIZE;
		AxAy[0] = all->player->px + ((AxAy[1] - all->player->py) / tan(M_2PI
					- angle));
		dxdy[0] = TILE_SIZE / tan(angle);
		dxdy[1] = -TILE_SIZE;
	}
	else
	{
		AxAy[1] = ((int)all->player->py / TILE_SIZE + 1) * TILE_SIZE;
		AxAy[0] = all->player->px + ((AxAy[1] - all->player->py) / tan(M_2PI
					- angle));
		dxdy[0] = -TILE_SIZE / tan(angle);
		dxdy[1] = TILE_SIZE;
	}
}

double	horz_dist(t_all all[1], double angle)
{
	double	AxAy[2];
	double	dxdy[2];
	int		hit_ij[2];

	horz_first_hit(all, angle, AxAy, dxdy);
	get_map_horz_idx(AxAy[0], AxAy[1], angle, hit_ij);
	while (is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		AxAy[0] += dxdy[0];
		AxAy[1] += dxdy[1];
		get_map_horz_idx(AxAy[0], AxAy[1], angle, hit_ij);
	}
	if (is_out_map(all, hit_ij))
		return (-1);
	get_map_horz_idx(AxAy[0], AxAy[1], angle, hit_ij);
	return (sqrt(pow((AxAy[0] - all->player->px), 2) + pow((AxAy[1]
					- all->player->py), 2)));
}
