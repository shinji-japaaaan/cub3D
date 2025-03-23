/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:56:01 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 11:31:09 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_function(t_all *all)
{
	update(all, all->player);
	img_raycast(all);
}

int	main(void)
{
	t_all	all[1];
	double	angle;
	char	*grid[] = {"1111111", "1010011", "1000001", "1000011", "1111111"};

	angle = 46;
	all->map->grid = (char **)malloc(sizeof(char *) * 6);
	for (int i = 0; i < 5; i++)
	{
		all->map->grid[i] = (char *)malloc(sizeof(char) * 10);
		all->map->grid[i] = strdup(grid[i]);
		printf("%s\n", all->map->grid[i]);
	}
	init_player(all->player);
	init_map(all->map);
	all->map->width = 7;
	all->map->height = 5;
	all->map->wind_width = all->map->width * TILE_SIZE;
	all->map->wind_height = all->map->height * TILE_SIZE;
	all->dPP = (double)(WIND_WIDTH / 2) / tan(cnv_rad(FOV_ANGLE / 2));
	printf("px py %lf %lf\n", all->player->px, all->player->py);
	initialize_window(all);
	mlx_hook(all->mlx_win, 17, 0, map_close, all);
	// mlx_hook(all->mlx_win, X_EVENT_KEY_PRESS, 1L << 0, &ft_key_hook, all);
	// mlx_hook(all->mlx_win, X_EVENT_KEY_RELEASE, (1L << 1), &ft_key_release,
	// 	all);
	mlx_key_hook(all->mlx_win, ft_key_hook, all);
	// img_raycast(all);
	mlx_loop_hook(all->mlx, (void *)loop_function, all);
	mlx_loop(all->mlx);
}
