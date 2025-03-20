/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:15:48 by karai             #+#    #+#             */
/*   Updated: 2025/03/20 21:33:58 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void get_map_vert_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int Bx;
	int By;

	if (90 <= angle && angle < 270)
		Bx = ceil(Ax) / 32 - 1;
	else
		Bx = ceil(Ax) / 32;
	By = ceil(Ay) / 32;
	hit_ij[1] = Bx;
	hit_ij[0] = By;
}

double vert_dist(t_all all[1], double angle)
{
	double Ax;
	double Ay;
	double dx;
	double dy;
	int hit_ij[2];

	if ((90 <= angle && angle < 270))
	{
		Ax = (int)all->player->px / 32 * 32;
		Ay = all->player->py + ((Ax - all->player->px) / tan(cnv_rad(360 - angle)));
		dy = TILE_SIZE / tan(cnv_rad(angle));
		dx = -TILE_SIZE;
	}
	else
	{
		Ax = ((int)all->player->px / 32 + 1) * 32;
		Ay = all->player->py + ((Ax - all->player->px) / tan(cnv_rad(360 - angle)));
		dy = -TILE_SIZE / tan(cnv_rad(angle));
		dx = TILE_SIZE;
	}
	printf("first_hit %lf %lf\n", Ax, Ay);
	// printf("dx %lf\n", dx);
	get_map_vert_idx(Ax, Ay, angle, hit_ij);
	// printf("%d %d\n", hit_ij[1], hit_ij[0]);
	while(is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		Ax += dx;
		Ay += dy;
		get_map_vert_idx(Ax, Ay, angle, hit_ij);
	}
	// printf("%d %d\n", hit_ij[1], hit_ij[0]);
	if (is_out_map(all, hit_ij))
		return(-1);
	get_map_vert_idx(Ax, Ay, angle, hit_ij);
	printf("last_hit %lf %lf\n", Ax, Ay);
	// printf("%d %d\n", hit_ij[1], hit_ij[0]);
	return(sqrt(pow((Ax-all->player->px), 2) + pow((Ay-all->player->py), 2)));
}
