/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/03/21 16:19:31 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define BUFFER_SIZE 1024
#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define TEXTURE_PATH "./textures/wall_texture.xpm"

typedef struct s_map
{
	char **grid;     // マップデータ (2D 配列)
	int width;       // マップの横幅
	int height;      // マップの縦幅
	char *tex_no;    // 北向きのテクスチャパス
	char *tex_so;    // 南向きのテクスチャパス
	char *tex_we;    // 西向きのテクスチャパス
	char *tex_ea;    // 東向きのテクスチャパス
	int floor_color; // 床の色 (RGB)
	int ceil_color;  // 天井の色 (RGB)
}				t_map;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    int img_width;
    int img_height;
} t_game;

//init.c
t_map *init_map(void);
void setup_window(t_game *game);
void load_texture(t_game *game);
void draw_image(t_game *game);

//parse_map.c
void parse_cub_file(char *filename, t_map *map);

void cleanup_and_exit(t_game *game);

#endif
