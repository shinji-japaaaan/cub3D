/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:40:19 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 10:42:12 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_backview(t_all *all, int floor_color, int ceil_color)
{
	int			i;
	int			j;
	long long	put_color;

	j = 0;
	while (j < WIND_HEIGHT)
	{
		i = 0;
		if (j < WIND_HEIGHT / 2)
		{
			put_color = ceil_color;
		}
		else
			put_color = floor_color;
		while (i < WIND_WIDTH)
		{
			i += 1;
			my_mlx_pixel_put(&(all->img), i, j, put_color);
		}
		j += 1;
	}
}

void	put_waltexture(t_all *all, int i)
{
	double	hd;
	double	vd;

	hd = horz_dist(all, all->ray_angle);
	vd = vert_dist(all, all->ray_angle);
	if (vd < 0)
		put_1line_case_hd(all, i, hd);
	else if (hd < 0)
		put_1line_case_vd(all, i, vd);
	else if (hd <= vd)
		put_1line_case_hd(all, i, hd);
	else
		put_1line_case_vd(all, i, vd);
}

void	img_raycast(t_all *all)
{
	int		i;

	i = 0;
	put_backview(all, all->map->floor_color, all->map->ceil_color);
	while (i < WIND_WIDTH)
	{
		all->ray_angle = all->player->ang + atan((i - WIND_WIDTH / 2)
				/ all->dpp);
		all->ray_angle = normalize_rad(all->ray_angle);
		put_waltexture(all, WIND_WIDTH - i - 1);
		i += 1;
	}
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img.img, 0, 0);
}
