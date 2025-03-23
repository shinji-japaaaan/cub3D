/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:19:37 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 11:31:36 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map_horz_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int Bx;
	int By;

	if (0 <= angle && angle < M_PI)
		By = floor(Ay/TILE_SIZE) - 1;
	else
		By = floor(Ay/TILE_SIZE);
	Bx = floor(Ax/TILE_SIZE);
	hit_ij[1] = Bx;
	hit_ij[0] = By;
}

double horz_dist(t_all all[1], double angle)
{
	double Ax;
	double Ay;
	double dx;
	double dy;
	int hit_ij[2];
	bool isHitHorz;

	isHitHorz = false;
	if (0 <= angle && angle < M_PI)
	{
		Ay = (int)all->player->py / TILE_SIZE * TILE_SIZE;
		Ax = all->player->px + ((Ay - all->player->py) / tan(M_2PI - angle));
		dx = TILE_SIZE / tan(angle);
		dy = -TILE_SIZE;
	}
	else
	{
		Ay = ((int)all->player->py / TILE_SIZE + 1) * TILE_SIZE;
		Ax = all->player->px + ((Ay - all->player->py) / tan(M_2PI - angle));
		dx = -TILE_SIZE / tan(angle);
		dy = TILE_SIZE;
	}
	get_map_horz_idx(Ax, Ay, angle, hit_ij);
	while(is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		Ax += dx;
		Ay += dy;
		get_map_horz_idx(Ax, Ay, angle, hit_ij);
	}
	if (is_out_map(all, hit_ij))
		return(-1);
	get_map_horz_idx(Ax, Ay, angle, hit_ij);
	// printf("horz Ax Ay %lf %lf\n", Ax, Ay);
	return(sqrt(pow((Ax-all->player->px), 2) + pow((Ay-all->player->py), 2)));
}


