/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:10:04 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/23 13:20:04 by sishizaw         ###   ########.fr       */
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

// パースチェック用
// int main(int argc, char **argv)
// {
//     t_map *map;

//     (void)argc;
//     map = init_map();
//     if (!map)
//     {
//         printf("Error: Failed to initialize map->\n");
//         return (1);
//     }

//     // .cubファイルを解析してマップ情報を取得
//     parse_cub_file(argv[1], map);

//     // 結果を出力（簡単な確認用）
//     printf("Textures:\n");
//     printf("NO: %s\n", map->tex_no);
//     printf("SO: %s\n", map->tex_so);
//     printf("WE: %s\n", map->tex_we);
//     printf("EA: %s\n", map->tex_ea);

//     printf("Floor Color: %d\n", map->floor_color);
//     printf("Ceil Color: %d\n", map->ceil_color);

//     printf("Map dimensions: %dx%d\n", map->height, map->width);
//     printf("Map:\n");
//     for (int i = 0; i < map->height; i++)
//     {
//         printf("%s\n", map->grid[i]);
//     }

//     // メモリ解放（必要に応じて）
//     for (int i = 0; i < map->height; i++)
//         free(map->grid[i]);
//     free(map->grid);
//     free(map->tex_no);
//     free(map->tex_so);
//     free(map->tex_we);
//     free(map->tex_ea);

//     return 0;
// }

//画像描画用
// int main(int argc, char **argv)
// {
//     t_map *map;
//     t_game *game;

//     (void)argc;
//     map = init_map();
//     if (!map)
//     {
//         printf("Error: Failed to initialize map->\n");
//         return (1);
//     }

//     // .cubファイルを解析してマップ情報を取得
//     parse_cub_file(argv[1], map);
//     game = malloc(sizeof(t_game));
//     if (!game)
//     {
//         perror("malloc failed");
//         return (EXIT_FAILURE);
//     }
//     game->img = NULL;
//     game->win = NULL;

//     setup_window(game);
//     load_texture(game);
//     draw_image(game);

//     mlx_key_hook(game->win, key_hook, game);
//     mlx_loop(game->mlx);
//     // メモリ解放（必要に応じて）
//     for (int i = 0; i < map->height; i++)
//         free(map->grid[i]);
//     free(map->grid);
//     free(map->tex_no);
//     free(map->tex_so);
//     free(map->tex_we);
//     free(map->tex_ea);

//     return 0;
// }

//メモリ管理関数用
int main(int argc, char **argv)
{
    t_map *map;
    t_game *game;

    (void)argc;
    map = init_map();
    if (!map)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);  // ここでも exit を使う
    }

    // .cubファイルを解析してマップ情報を取得
    parse_cub_file(argv[1], map);
    if (!validate_map(map->grid))
        exit_with_error(map, "Invalid map format");
    
    game = malloc(sizeof(t_game));
    if (!game)
        exit_with_error(map, "malloc failed");
    game->img = NULL;
    game->win = NULL;

    setup_window(game);
    load_texture(game);
    draw_image(game);

    mlx_key_hook(game->win, key_hook, game);
    mlx_loop(game->mlx);

    free_all(map);  // メモリ解放
    cleanup_and_exit(game, EXIT_SUCCESS);  // 正常終了
}