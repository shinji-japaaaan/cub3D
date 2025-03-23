/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:38:35 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 10:13:22 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_window(t_all *all)
{
	size_t	i;
	int		tmp1;

	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, WIND_WIDTH, WIND_HEIGHT, "./cub3d");
	all->img.img = mlx_new_image(all->mlx, WIND_WIDTH, WIND_HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &(all->img.bits_per_pixel),
			&(all->img.line_length), &(all->img.endian));
	// all->map_no = mlx_xpm_file_to_image(all->mlx, all->map->tex_no, &tmp1,
	// 		&tmp1);
	// all->map_so = mlx_xpm_file_to_image(all->mlx, all->map->tex_so, &tmp1,
	// 		&tmp1);
	// all->map_we = mlx_xpm_file_to_image(all->mlx, all->map->tex_we, &tmp1,
	// 		&tmp1);
	// all->map_ea = mlx_xpm_file_to_image(all->mlx, all->map->tex_ea, &tmp1,
	// 		&tmp1);
	// i = 0;
	// while ( // condition)
	// {
	// 	// to do
	// 	i += 1;
	// }
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	img_show(t_all *all)
{
}

int	map_close(t_all *all)
{
	// free_all(all); to be implemeted
	printf("You gave up.\n");
	exit(0);
}

int	ft_key_press(int keycode, t_all *all)
{
	printf("keycode %d\n", keycode);
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == 'w')
		all->player->walkDirection = MOVE_FRONT;
	if (keycode == 'd')
	{
		printf("touch d\n");
		all->player->walkDirection = MOVE_RIGHT;
	}
	if (keycode == 's')
	{
		all->player->walkDirection = MOVE_BACK;
	}
	if (keycode == 'a')
	{
		all->player->walkDirection = MOVE_LEFT;
	}
	if (keycode == RIGHT_ARROW)
	{
		all->player->turnDirection = TURN_RIGHT;
	}
	if (keycode == LEFT_ARROW)
	{
		all->player->turnDirection = TURN_LEFT;
	}
	return (0);
}

int	ft_key_release(int keycode, t_all *all)
{
	if (keycode == 'w' || keycode == 'd' || keycode == 's' || keycode == 'a')
		all->player->walkDirection = 0;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
	{
		all->player->turnDirection = 0;
	}
	return (0);
}

int	ft_key_hook(int keycode, t_all *all)
{
	double		moveStep;
	double		newPlayerX;
	double		newPlayerY;
	t_player	*player;

	printf("keycode %d\n", keycode);
	if (keycode == ESCAPE)
		exit(0);
	player = all->player;
	if (keycode == 'w')
	{
		newPlayerX = player->px + cos(player->ang) * player->moveSpeed;
		newPlayerY = player->py + sin(player->ang) * -1 * player->moveSpeed;
	}
	else if (keycode == 's')
	{
		newPlayerX = player->px + cos(player->ang) * -1 * player->moveSpeed;
		newPlayerY = player->py + sin(player->ang) * player->moveSpeed;
	}
	else if (keycode == 'a')
	{
		newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(90)))
			* player->moveSpeed;
		newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(90)))
			* -1 * player->moveSpeed;
	}
	else if (keycode == 'd')
	{
		newPlayerX = player->px + cos(normalize_rad(player->ang + cnv_rad(90)))
			* -1 * player->moveSpeed;
		newPlayerY = player->py + sin(normalize_rad(player->ang + cnv_rad(90)))
			* player->moveSpeed;
	}
	else if (keycode == RIGHT_ARROW)
	{
		player->ang -= player->rotSpeed;
	}
	else if (keycode == LEFT_ARROW)
	{
		player->ang += player->rotSpeed;
	}
	else
	{
		newPlayerX = player->px;
		newPlayerY = player->py;
	}
	if (!is_WallInside(all, newPlayerX, newPlayerY))
	{
		player->px = newPlayerX;
		player->py = newPlayerY;
	}
	player->ang =normalize_rad(player->ang);
	printf("px py %lf %lf %lf\n", player->px, player->py, player->ang * 180 / M_PI);
}
