/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:38:35 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 00:32:57 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_xpm(t_all *all, t_xpm *xpm, char *tex_path)
{
	int	tmp1;

	xpm->map = mlx_xpm_file_to_image(all->mlx, tex_path, &tmp1, &tmp1);
	xpm->addr = mlx_get_data_addr(xpm->map, &(xpm->bpp), &(xpm->line_length),
			&(xpm->endian));
}

void	initialize_window(t_all *all)
{
	size_t	i;
	int		tmp1;

	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, WIND_WIDTH, WIND_HEIGHT, "./cub3d");
	all->img.img = mlx_new_image(all->mlx, WIND_WIDTH, WIND_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &(all->img.bits_per_pixel),
			&(all->img.line_length), &(all->img.endian));
	get_xpm(all, all->xpm_no, all->map->tex_no);
	get_xpm(all, all->xpm_so, all->map->tex_so);
	get_xpm(all, all->xpm_ea, all->map->tex_ea);
	get_xpm(all, all->xpm_we, all->map->tex_we);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_xpm *xpm, int x, int y)
{
	char	*src;

	src = xpm->addr + (y * xpm->line_length + x * (xpm->bpp / 8));
	return (*(int *)src);
}
