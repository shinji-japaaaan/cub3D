/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 09:50:17 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub3d.h"

// static int key_hook(int keycode, t_game *game)
// {
//     if (keycode == 65307)
//         cleanup_and_exit(game, EXIT_SUCCESS);
//     return (0);
// }

// static void *init_mlx(t_game *game)
// {
//     void *mlx;

//     mlx = mlx_init();
//     if (!mlx)
//     {
//         perror("mlx_init failed");
//         free_all(game->map);
//         cleanup_and_exit(game, EXIT_FAILURE);
//     }
//     return (mlx);
// }

// static void *init_window(t_game *game)
// {
//     void *win;

//     win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
//     if (!win)
//     {
//         perror("mlx_new_window failed");
//         free_all(game->map);
//         cleanup_and_exit(game, EXIT_FAILURE);
//     }
//     return (win);
// }

// void *load_texture(t_game *game, char *path)
// {
//     void *img;

//     img = mlx_xpm_file_to_image(game->mlx, path,
//         &game->img_width, &game->img_height);
//     if (!img)
//     {
//         perror("Failed to load texture");
//         return NULL;
//     }
//     return (img);
// }

// void init_textures(t_game *game)
// {
//     game->tex_no_img = load_texture(game, game->map->tex_no);
//     if (!game->tex_no_img)
//         printf("Failed to load north texture\n");

//     game->tex_so_img = load_texture(game, game->map->tex_so);
//     if (!game->tex_so_img)
//         printf("Failed to load south texture\n");

//     game->tex_we_img = load_texture(game, game->map->tex_we);
//     if (!game->tex_we_img)
//         printf("Failed to load west texture\n");

//     game->tex_ea_img = load_texture(game, game->map->tex_ea);
//     if (!game->tex_ea_img)
//         printf("Failed to load east texture\n");
// }

// void start_game(t_game *game, t_map *map)
// {
//     game->map = map;
//     game->mlx = init_mlx(game);
//     game->win = init_window(game);
//     mlx_clear_window(game->mlx, game->win);
//     init_textures(game);
//     if (game->tex_no_img)
//         mlx_put_image_to_window(game->mlx, game->win,
//         game->tex_no_img, 0, 0);
//     if (game->tex_so_img)
//         mlx_put_image_to_window(game->mlx, game->win,
//         game->tex_so_img, 200, 0);
//     if (game->tex_we_img)
//         mlx_put_image_to_window(game->mlx, game->win,
//         game->tex_we_img, 0, 200);
//     if (game->tex_ea_img)
//     mlx_put_image_to_window(game->mlx, game->win,
//         game->tex_ea_img, 200, 200);
//     mlx_key_hook(game->win, key_hook, game);
//     mlx_loop(game->mlx);
// }
