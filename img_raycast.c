#include "cub3d.h"

void	put_1line(t_all *all, int i, double wallStripHeight, long long color)
{
	int	j;
	int	stop;

	wallStripHeight *= SCALE;
	j = WIND_HEIGHT / 2 - ceil(wallStripHeight) / 2;
	if (j < 0)
		j = 0;
	stop = ceil(wallStripHeight) + j;
	while (j < WIND_HEIGHT && j < stop)
	{
		my_mlx_pixel_put(&(all->img), i, j, color);
		j += 1;
	}
}

int	get_horz_idx(t_all *all, double angle, double dist, int case_hd)
{
	double	tx;
	double	ty;
	double	tmp;

	if (case_hd == 1)
	{
		tx = all->player->px + cos(angle) * dist;
		tmp = fmod(tx, (double)TILE_SIZE) * (double)IMG_SIZE
			/ (double)TILE_SIZE;
		return (floor(tmp));
	}
	else
	{
		ty = all->player->py - sin(angle) * dist;
		tmp = fmod(ty, (double)TILE_SIZE) * (double)IMG_SIZE
			/ (double)TILE_SIZE;
		return (floor(tmp));
	}
}

void	put_1line_rev(t_all *all, int i, double wallStripHeight, double angle,
		double dist, int case_hd)
{
	int		j;
	int		stop;
	int		img_vert_idx;
	int		img_horz_idx;
	double	temp;
	int		offset;
	int		color;

	img_horz_idx = get_horz_idx(all, angle, dist, case_hd);
	wallStripHeight *= SCALE;
	j = 0;
	offset = ceil(((double)WIND_HEIGHT - wallStripHeight) / 2);
	stop = ceil(wallStripHeight) + offset;
	temp = (double)IMG_SIZE / wallStripHeight;
	while (j < WIND_HEIGHT && j < stop)
	{
		if (j < offset)
		{
			j += 1;
			continue ;
		}
		img_vert_idx = ceil(temp * (j - offset));
		if (case_hd == 1)
		{
			if (0 <= angle && angle < M_PI)
				color = my_mlx_pixel_get(all->xpm_no, img_horz_idx,
						img_vert_idx);
			else
				color = my_mlx_pixel_get(all->xpm_so, IMG_SIZE - 1
						- img_horz_idx, img_vert_idx);
		}
		else
		{
			if (M_1by2PI <= angle && angle < M_3by2PI)
				color = my_mlx_pixel_get(all->xpm_we, IMG_SIZE - 1
						- img_horz_idx, img_vert_idx);
			else
				color = my_mlx_pixel_get(all->xpm_ea, img_horz_idx,
						img_vert_idx);
		}
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

void	put_1line_case_hd_vd(t_all *all, double ray_angle, int i,
		int case_hd_vd, double hd, double vd, double angle)
{
	double	perpDistance;
	double	wallStripHeight;

	if (case_hd_vd == 1)
	{
		perpDistance = hd * cos(ray_angle - all->player->ang);
		wallStripHeight = ((double)TILE_SIZE / perpDistance) * all->dPP;
		put_1line_rev(all, i, wallStripHeight, angle, hd, 1);
	}
	else
	{
		perpDistance = vd * cos(ray_angle - all->player->ang);
		wallStripHeight = (TILE_SIZE / perpDistance) * all->dPP;
		put_1line_rev(all, i, wallStripHeight, angle, vd, 2);
	}
}

void	img_raycast(t_all *all)
{
	int		i;
	double	ray_angle;
	double	hd;
	double	vd;
	double	stp_ang;
	double	wallStripHeight;
	double	perpDistance;

	ray_angle = all->player->ang + cnv_rad(FOV_ANGLE / 2);
	ray_angle = normalize_rad(ray_angle);
	stp_ang = cnv_rad((double)FOV_ANGLE) / (double)WIND_WIDTH;
	i = 0;
	put_backview(all, all->map->floor_color, all->map->ceil_color);
	while (i < WIND_WIDTH)
	{
		hd = horz_dist(all, ray_angle);
		vd = vert_dist(all, ray_angle);
		if (vd < 0)
			put_1line_case_hd_vd(all, ray_angle, i, 1, hd, vd, ray_angle);
		else if (hd < 0)
			put_1line_case_hd_vd(all, ray_angle, i, 2, hd, vd, ray_angle);
		else if (hd <= vd)
			put_1line_case_hd_vd(all, ray_angle, i, 1, hd, vd, ray_angle);
		else
			put_1line_case_hd_vd(all, ray_angle, i, 2, hd, vd, ray_angle);
		ray_angle -= stp_ang;
		ray_angle = normalize_rad(ray_angle);
		i += 1;
	}
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img.img, 0, 0);
}
