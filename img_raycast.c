/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:40:19 by karai             #+#    #+#             */
/*   Updated: 2025/04/01 23:20:19 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_img_horz_idx(t_all *all, double dist, int case_hd)
// {
// 	double	tx;
// 	double	ty;
// 	double	tmp;

// 	if (case_hd == 1)
// 	{
// 		tx = all->player->px + cos(all->ray_angle) * dist;
// 		tmp = fmod(tx, (double)TILE_SIZE) * (double)IMG_SIZE
// 			/ (double)TILE_SIZE;
// 		return (floor(tmp));
// 	}
// 	else
// 	{
// 		ty = all->player->py - sin(all->ray_angle) * dist;
// 		tmp = fmod(ty, (double)TILE_SIZE) * (double)IMG_SIZE
// 			/ (double)TILE_SIZE;
// 		return (floor(tmp));
// 	}
// }

int	get_img_horz_idx_h(t_all *all, double dist)
{
	double	tx;
	double	ty;
	double	tmp;

	tx = all->player->px + cos(all->ray_angle) * dist;
	tmp = fmod(tx, (double)TILE_SIZE) * (double)IMG_SIZE / (double)TILE_SIZE;
	return (floor(tmp));
}

int	get_img_horz_idx_v(t_all *all, double dist)
{
	double	tx;
	double	ty;
	double	tmp;

	ty = all->player->py - sin(all->ray_angle) * dist;
	tmp = fmod(ty, (double)TILE_SIZE) * (double)IMG_SIZE / (double)TILE_SIZE;
	return (floor(tmp));
}

// void	put_1line_rev(t_all *all, int i, double dist, int case_hd)
// {
// 	int		j;
// 	int		img_vert_idx;
// 	int		img_horz_idx;
// 	double	temp;
// 	int		color;

// 	img_horz_idx = get_img_horz_idx(all, dist, case_hd);
// 	j = 0;
// 	temp = (double)IMG_SIZE / all->wallStripHeight;
// 	if (all->offset > 0)
// 		j = all->offset;
// 	while (j < WIND_HEIGHT && j < all->stop)
// 	{
// 		img_vert_idx = ceil(temp * (j - all->offset));
// 		if (case_hd == 1)
// 		{
// 			if (0 <= all->ray_angle && all->ray_angle < M_PI)
// 				color = my_mlx_pixel_get(all->xpm_no, img_horz_idx,
// 						img_vert_idx);
// 			else
// 				color = my_mlx_pixel_get(all->xpm_so, IMG_SIZE - 1
// 						- img_horz_idx, img_vert_idx);
// 		}
// 		else
// 		{
// 			if (M_1by2PI <= all->ray_angle && all->ray_angle < M_3by2PI)
// 				color = my_mlx_pixel_get(all->xpm_we, IMG_SIZE - 1
// 						- img_horz_idx, img_vert_idx);
// 			else
// 				color = my_mlx_pixel_get(all->xpm_ea, img_horz_idx,
// 						img_vert_idx);
// 		}
// 		my_mlx_pixel_put(&(all->img), i, j, color);
// 		j += 1;
// 	}
// }

void	put_1line_vert(t_all *all, int i, double dist)
{
	int		j;
	int		img_vert_idx;
	int		img_horz_idx;
	double	temp;
	int		color;

	img_horz_idx = get_img_horz_idx_v(all, dist);
	j = 0;
	temp = (double)IMG_SIZE / all->wallStripHeight;
	if (all->offset > 0)
		j = all->offset;
	while (j < WIND_HEIGHT && j < all->stop)
	{
		img_vert_idx = ceil(temp * (j - all->offset));
		if (M_ONETWO_PI <= all->ray_angle && all->ray_angle < M_THREETWO_PI)
			color = my_mlx_pixel_get(all->xpm_we, IMG_SIZE - 1 - img_horz_idx,
					img_vert_idx);
		else
			color = my_mlx_pixel_get(all->xpm_ea, img_horz_idx, img_vert_idx);
		my_mlx_pixel_put(&(all->img), i, j, color);
		j += 1;
	}
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
	if (all->offset > 0)
		j = all->offset;
	while (j < WIND_HEIGHT && j < all->stop)
	{
		img_vert_idx = ceil(temp * (j - all->offset));
		if (0 <= all->ray_angle && all->ray_angle < M_PI)
			color = my_mlx_pixel_get(all->xpm_no, img_horz_idx, img_vert_idx);
		else
			color = my_mlx_pixel_get(all->xpm_so, IMG_SIZE - 1 - img_horz_idx,
					img_vert_idx);
		my_mlx_pixel_put(&(all->img), i, j, color);
		j += 1;
	}
}

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

void	put_1line_case_vd(t_all *all, int i, double vd)
{
	double	perp_distance;
	int		img_horz_idx;

	perp_distance = vd * cos(all->ray_angle - all->player->ang);
	all->wallStripHeight = (TILE_SIZE / perp_distance) * all->dPP;
	all->wallStripHeight *= SCALE;
	all->offset = ceil(((double)WIND_HEIGHT - all->wallStripHeight) / 2);
	all->stop = ceil(all->wallStripHeight) + all->offset;
	put_1line_vert(all, i, vd);
}

void	put_1line_case_hd(t_all *all, int i, double hd)
{
	double	perp_distance;

	perp_distance = hd * cos(all->ray_angle - all->player->ang);
	all->wallStripHeight = ((double)TILE_SIZE / perp_distance) * all->dPP;
	all->wallStripHeight *= SCALE;
	all->offset = ceil(((double)WIND_HEIGHT - all->wallStripHeight) / 2);
	all->stop = ceil(all->wallStripHeight) + all->offset;
	put_1line_horz(all, i, hd);
}

void	put_waltexture(t_all *all, double stp_ang, int i)
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
	all->ray_angle -= stp_ang;
	all->ray_angle = normalize_rad(all->ray_angle);
}

void	img_raycast(t_all *all)
{
	int		i;
	double	stp_ang;

	all->ray_angle = all->player->ang + cnv_rad(FOV_ANGLE / 2);
	all->ray_angle = normalize_rad(all->ray_angle);
	stp_ang = cnv_rad((double)FOV_ANGLE) / (double)WIND_WIDTH;
	i = 0;
	put_backview(all, all->map->floor_color, all->map->ceil_color);
	while (i < WIND_WIDTH)
	{
		put_waltexture(all, stp_ang, i);
		i += 1;
	}
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img.img, 0, 0);
}
