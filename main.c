/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:20:02 by karai             #+#    #+#             */
/*   Updated: 2025/03/20 12:13:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_map *map;
	t_all all[1];

	if (argc != 2)
	{
		printf("The number of argument is wrong\n");
		return (1);
	}
	map = get_info_from_file(argv[1]);

	initialize_window(all);
	mlx_hook(all->mlx_win, 17, 0, map_close, all);
	mlx_key_hook(all->mlx_win, ft_key_hook, all);
	mlx_loop(all->mlx);
}
