/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:19:37 by karai             #+#    #+#             */
/*   Updated: 2025/03/20 21:15:21 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void get_map_horz_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int Bx;
	int By;

	if (0 <= angle && angle < 180)
		By = ceil(Ay) / 32 - 1;
	else
		By = ceil(Ay) / 32;
	Bx = ceil(Ax) / 32;
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

	if (0 <= angle && angle < 180)
	{
		Ay = (int)all->player->py / 32 * 32;
		Ax = all->player->px + ((Ay - all->player->py) / tan(cnv_rad(360 - angle)));
		dx = TILE_SIZE / tan(cnv_rad(angle));
		dy = -TILE_SIZE;
	}
	else
	{
		Ay = ((int)all->player->py / 32 + 1) * 32;
		Ax = all->player->px + ((Ay - all->player->py) / tan(cnv_rad(360 - angle)));
		dx = -TILE_SIZE / tan(cnv_rad(angle));
		dy = TILE_SIZE;
	}
	// printf("first_hit %lf %lf\n", Ax, Ay);
	// printf("dx %lf\n", dx);
	get_map_horz_idx(Ax, Ay, angle, hit_ij);
	// printf("%d %d\n", hit_ij[1], hit_ij[0]);
	while(is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		Ax += dx;
		Ay += dy;
		get_map_horz_idx(Ax, Ay, angle, hit_ij);
	}
	printf("%d %d\n", hit_ij[1], hit_ij[0]);
	if (is_out_map(all, hit_ij))
		return(-1);
	get_map_horz_idx(Ax, Ay, angle, hit_ij);
	printf("last_hit %lf %lf\n", Ax, Ay);
	// printf("%d %d\n", hit_ij[1], hit_ij[0]);
	return(sqrt(pow((Ax-all->player->px), 2) + pow((Ay-all->player->py), 2)));
}


