/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:10:04 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/21 16:17:38 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//初期化check用
// int main(void)
// {
//     t_map *map;

//     map = init_map();
//     if (!map)
//     {
//         printf("Error: Failed to initialize map->\n");
//         return (1);
//     }
    
//     // 初期化が正しく行われたか確認
//     printf("Map initialized:\n");
//     printf("Width: %d, Height: %d\n", map->width, map->height);
//     printf("Textures: NO=%p, SO=%p, WE=%p, EA=%p\n",
//            (void *)map->tex_no, (void *)map->tex_so,
//            (void *)map->tex_we, (void *)map->tex_ea);
//     printf("Floor Color: %d, Ceiling Color: %d\n",
//            map->floor_color, map->ceil_color);

//     // メモリ解放
//     free(map);
//     return (0);
// }

//パースチェック用
// int main(int argc, char **argv)
// {
//     t_map *map;

//     map = init_map();
//     if (!map)
//     {
//         printf("Error: Failed to initialize map->\n");
//         return (1);
//     }

//     if (argc != 2)
//     {
//         write(2, "Usage: ./cub3d <file.cub>\n", 26);
//         return (1);
//     }

//     // .cubファイルのパース
//     parse_cub_file(argv[1], map);

//     // パースされたデータの表示
//     write(1, "Parsed Data:\n", 13);
//     write(1, map->tex_no, ft_strlen(map->tex_no));
//     write(1, "\n", 1);
//     write(1, map->tex_so, ft_strlen(map->tex_so));
//     write(1, "\n", 1);
//     write(1, map->tex_we, ft_strlen(map->tex_we));
//     write(1, "\n", 1);
//     write(1, map->tex_ea, ft_strlen(map->tex_ea));
//     write(1, "\n", 1);
//     printf("Floor color: %d\n", map->floor_color);
//     printf("Ceiling color: %d\n", map->ceil_color);

//     // メモリ解放
//     free(map->tex_no);
//     free(map->tex_so);
//     free(map->tex_we);
//     free(map->tex_ea);

//     return (0);
// }

//mlx初期化

void cleanup_and_exit(t_game *game)
{
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    free(game);
    exit(EXIT_SUCCESS);
}

int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // ESCキーで終了
        cleanup_and_exit(game);
    return (0);
}

int main(void)
{
    t_game *game = malloc(sizeof(t_game));
    if (!game)
    {
        perror("malloc failed");
        return (EXIT_FAILURE);
    }
    
    game->img = NULL;
    game->win = NULL;

    setup_window(game);
    load_texture(game);
    draw_image(game);

    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);

    return (0);
}


