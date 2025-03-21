/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/21 15:33:06 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map *init_map(void)
{
    t_map *map;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->tex_no = NULL;
    map->tex_so = NULL;
    map->tex_we = NULL;
    map->tex_ea = NULL;
    map->floor_color = -1; // 未設定時は -1
    map->ceil_color = -1;
    return (map);
}

void setup_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        perror("mlx_init failed");
        exit(EXIT_FAILURE);
    }
    
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!game->win)
    {
        perror("mlx_new_window failed");
        exit(EXIT_FAILURE);
    }

    // 画面の背景をクリア
    mlx_clear_window(game->mlx, game->win);
}

void load_texture(t_game *game)
{
    game->img = mlx_xpm_file_to_image(game->mlx, TEXTURE_PATH, 
                                      &game->img_width, &game->img_height);
    if (!game->img)
    {
        perror("Failed to load texture");
        cleanup_and_exit(game);
    }
}

void draw_image(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->win, game->img, 100, 100);
}