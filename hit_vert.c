/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:15:48 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 11:31:30 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_vert_idx(double Ax, double Ay, double angle, int hit_ij[2])
{
	int	Bx;
	int	By;

	if (M_1by2PI <= angle && angle < M_3by2PI)
		Bx = floor(Ax / TILE_SIZE) - 1;
	else
		Bx = floor(Ax / TILE_SIZE);
	By = floor(Ay / TILE_SIZE);
	hit_ij[1] = Bx;
	hit_ij[0] = By;
}

double	vert_dist(t_all all[1], double angle)
{
	double	Ax;
	double	Ay;
	double	dx;
	double	dy;
	int		hit_ij[2];

	if (M_1by2PI <= angle && angle < M_3by2PI)
	{
		Ax = (int)all->player->px / TILE_SIZE * TILE_SIZE;
		Ay = all->player->py - ((Ax - all->player->px) * tan(angle));
		dy = TILE_SIZE * tan(angle);
		dx = -TILE_SIZE;
	}
	else
	{
		Ax = ((int)all->player->px / TILE_SIZE + 1) * TILE_SIZE;
		Ay = all->player->py - ((Ax - all->player->px) * tan(angle));
		dy = -TILE_SIZE * tan(angle);
		dx = TILE_SIZE;
	}
	get_map_vert_idx(Ax, Ay, angle, hit_ij);
	while (is_out_map(all, hit_ij) == false && is_wall(all, hit_ij) == false)
	{
		Ax += dx;
		Ay += dy;
		get_map_vert_idx(Ax, Ay, angle, hit_ij);
	}
	if (is_out_map(all, hit_ij))
		return (-1);
	get_map_vert_idx(Ax, Ay, angle, hit_ij);
	// printf("vert Ax Ay %lf %lf\n", Ax, Ay);
	return (sqrt(pow((Ax - all->player->px), 2) + pow((Ay - all->player->py),
				2)));
}
