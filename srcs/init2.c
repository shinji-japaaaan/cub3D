/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/28 21:21:27 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESCキーで終了
        cleanup_and_exit(game, EXIT_SUCCESS);
    return (0);
}

static void *init_mlx(t_game *game)
{
    void *mlx;

    mlx = mlx_init();
    if (!mlx)
    {
        perror("mlx_init failed");
        free_all(game->map);
        cleanup_and_exit(game, EXIT_FAILURE);
    }
    return (mlx);
}

static void *init_window(t_game *game)
{
    void *win;

    win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!win)
    {
        perror("mlx_new_window failed");
        free_all(game->map);
        cleanup_and_exit(game, EXIT_FAILURE);
    }
    return (win);
}

static void *init_texture(t_game *game)
{
    void *img;

    img = mlx_xpm_file_to_image(game->mlx, TEXTURE_PATH, 
        &game->img_width, &game->img_height);
    if (!img)
    {
        perror("Failed to load texture");
        free_all(game->map);
        cleanup_and_exit(game, EXIT_FAILURE);
    }
    return (img);
}

void start_game(t_game *game, t_map *map)
{
    game->map = map;
    game->mlx = init_mlx(game);
    game->win = init_window(game);
    mlx_clear_window(game->mlx, game->win);
    game->img = init_texture(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 100, 100);
    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);
}