/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:10:04 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 16:50:38 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_cub_file(const char *filename, t_map *map)
{
	char	**lines;

	lines = read_lines(filename);
	if (!lines)
		print_error_and_exit("Error: Failed to read file\n");
	if (!validate_cub_format(lines))
	{
		free_lines(lines);
		print_error_and_exit("Error: Invalid .cub file format\n");
	}
	process_lines(lines, map);
	free_lines(lines);
}

static int	validate_map(t_map *map)
{
	if (!check_map_structure(map))
	{
		free_all(map);
		exit_with_error("Invalid map format");
	}
	else if (!check_map_content(map))
	{
		free_all(map);
		exit_with_error("Invalid map format");
	}
	return (1);
}

void	loop_function(t_all *all)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (DT < current_time - all->last_scan)
	{
		all->last_scan = current_time;
		update(all, all->player);
		img_raycast(all);
	}
}

int	main(int argc, char **argv)
{
	t_all	all[1];

	if (argc != 2)
	{
		printf("Error: You must provide exactly two .cub files.\n");
		exit(1);
	}
	initialize_all(all);
	init_map(all->map);
	parse_cub_file(argv[1], all->map);
	validate_map(all->map);
	all->map->wind_width = all->map->width * TILE_SIZE;
	all->map->wind_height = all->map->height * TILE_SIZE;
	init_player(all->map, all->player);
	all->dpp = (double)(WIND_WIDTH / 2) / tan(cnv_rad(FOV_ANGLE / 2));
	initialize_window(all);
	mlx_hook(all->mlx_win, 17, 0, map_close, all);
	mlx_hook(all->mlx_win, X_EVENT_KEY_PRESS, 1L << 0, &ft_key_press, all);
	mlx_hook(all->mlx_win, X_EVENT_KEY_RELEASE, (1L << 1), &ft_key_release,
		all);
	mlx_loop_hook(all->mlx, (void *)loop_function, all);
	mlx_loop(all->mlx);
	free_all(all->map);
}
