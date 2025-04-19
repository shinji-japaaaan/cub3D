/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_vd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:50:15 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 09:56:10 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_img_horz_idx_v(t_all *all, double dist)
{
	double	ty;
	double	tmp;

	ty = all->player->py - sin(all->ray_angle) * dist;
	tmp = fmod(ty, (double)TILE_SIZE) * (double)IMG_SIZE / (double)TILE_SIZE;
	return (floor(tmp));
}

void	put_1line_case_vd(t_all *all, int i, double vd)
{
	double	perp_distance;

	perp_distance = vd * cos(all->ray_angle - all->player->ang);
	all->wall_strip_height = (TILE_SIZE / perp_distance) * all->dpp;
	all->wall_strip_height *= SCALE;
	all->offset = ((double)WIND_HEIGHT - all->wall_strip_height) / 2;
	all->stop = ceil(all->wall_strip_height + all->offset);
	put_1line_vert(all, i, vd);
}

void	put_1line_vert(t_all *all, int i, double dist)
{
	int		j;
	int		img_vert_idx;
	int		img_horz_idx;
	double	temp;
	int		color;

	img_horz_idx = get_img_horz_idx_v(all, dist);
	j = 0;
	temp = (double)IMG_SIZE / all->wall_strip_height;
	while (j < WIND_HEIGHT && j < all->stop)
	{
		if (j < all->offset)
		{
			j += 1;
			continue ;
		}
		img_vert_idx = floor(temp * ((double)j - all->offset));
		if (M_ONETWO_PI <= all->ray_angle && all->ray_angle < M_THREETWO_PI)
			color = my_mlx_pixel_get(all->xpm_we, IMG_SIZE - 1 - img_horz_idx,
					img_vert_idx);
		else
			color = my_mlx_pixel_get(all->xpm_ea, img_horz_idx, img_vert_idx);
		my_mlx_pixel_put(&(all->img), i, j, color);
		j += 1;
	}
}
