/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:51:56 by karai             #+#    #+#             */
/*   Updated: 2025/04/02 23:34:13 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_img_horz_idx_h(t_all *all, double dist)
{
	double	tx;
	double	ty;
	double	tmp;

	tx = all->player->px + cos(all->ray_angle) * dist;
	tmp = fmod(tx, (double)TILE_SIZE) * (double)IMG_SIZE / (double)TILE_SIZE;
	return (floor(tmp));
}

void	put_1line_case_hd(t_all *all, int i, double hd)
{
	double perp_distance;

	perp_distance = hd * cos(all->ray_angle - all->player->ang);
	all->wallStripHeight = ((double)TILE_SIZE / perp_distance) * all->dPP;
	all->wallStripHeight *= SCALE;
	all->offset = ((double)WIND_HEIGHT - all->wallStripHeight) / 2;
	// printf("%f\n", all->offset);
	all->stop = ceil(all->wallStripHeight + all->offset);
	put_1line_horz(all, i, hd);
}

void	put_1line_horz(t_all *all, int i, double dist)
{
	int		j;
	int		img_vert_idx;
	int		img_horz_idx;
	double	temp;
	int		color;

	img_horz_idx = get_img_horz_idx_h(all, dist);
	j = 0;
	temp = (double)IMG_SIZE / all->wallStripHeight;
	bool first = true;
	while (j < WIND_HEIGHT && j < all->stop)
	{
		if (j < all-> offset)
		{
			j += 1;
			continue;
		}
		// if (first)
		// {
		// 	printf("%d\n", j);
		// 	first = false;
		// }
		img_vert_idx = floor(temp * ((double)j - all->offset));
		if (0 <= all->ray_angle && all->ray_angle < M_PI)
			color = my_mlx_pixel_get(all->xpm_no, img_horz_idx, img_vert_idx);
		else
			color = my_mlx_pixel_get(all->xpm_so, IMG_SIZE - 1 - img_horz_idx,
					img_vert_idx);
		my_mlx_pixel_put(&(all->img), i, j, color);
		j += 1;
	}
}
