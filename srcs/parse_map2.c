/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 06:38:22 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_flag(int *flag, int *error)
{
	if (*flag)
		*error = 1;
	*flag = 1;
}

void	print_error_and_exit(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

void	print_perror_and_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	exit_with_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (game)
	{
		if (game->tex_no_img)
			mlx_destroy_image(game->mlx, game->tex_no_img);
		if (game->tex_so_img)
			mlx_destroy_image(game->mlx, game->tex_so_img);
		if (game->tex_ea_img)
			mlx_destroy_image(game->mlx, game->tex_ea_img);
		if (game->tex_we_img)
			mlx_destroy_image(game->mlx, game->tex_we_img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
	exit(exit_code);
}

int	error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}


