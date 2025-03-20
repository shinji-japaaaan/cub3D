/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:38:35 by karai             #+#    #+#             */
/*   Updated: 2025/03/20 12:18:18 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_window(t_all *all)
{
	size_t	i;
	int		tmp1;

	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, WIND_WIDTH, WIND_HEIGHT, "./cub3d");
	all->map_no = mlx_xpm_file_to_image(all->mlx, all->map->tex_no, &tmp1,
			&tmp1);
	all->map_so = mlx_xpm_file_to_image(all->mlx, all->map->tex_so, &tmp1,
			&tmp1);
	all->map_we = mlx_xpm_file_to_image(all->mlx, all->map->tex_we, &tmp1,
			&tmp1);
	all->map_ea = mlx_xpm_file_to_image(all->mlx, all->map->tex_ea, &tmp1,
			&tmp1);
	// i = 0;
	// while ( // condition)
	// {
	// 	// to do
	// 	i += 1;
	// }
}

int	map_close(t_all *all)
{
	// free_all(all); to be implemeted
	printf("You gave up.\n");
	exit(0);
}

int	ft_key_hook(int keycode, t_all *all)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == 'w')
	{
		// to do
	}
	if (keycode == 'd')
	{
		// to do
	}
	if (keycode == 's')
	{
		// to do
	}
	if (keycode == 'a')
	{
		// to do
	}
	if (keycode == RIGHT_ARROW)
	{
		// to do
	}
	if (keycode == LEFT_ARROW)
	{
		// to do
	}
	return (0);
}
