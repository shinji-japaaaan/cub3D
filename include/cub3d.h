/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/03/21 13:48:54 by sishizaw         ###   ########.fr       */
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

# define TILE_SIZE 32
# define WIND_HEIGHT 240
# define WIND_WIDTH 320
# define RAY_CAST_ANGLE 30
# define M_PI 3.14159265358979323846

# define UP_ARROW 65362
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define ESCAPE 65307

#define BUFFER_SIZE 1024

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

typedef struct s_ray
{
	double dir_x;   // レイの向き (x成分)
	double dir_y;   // レイの向き (y成分)
	double delta_x; // DDA用のx方向の増分
	double delta_y; // DDA用のy方向の増分
	int map_x;      // レイが当たったマップのx座標
	int map_y;      // レイが当たったマップのy座標
	int side;       // 0: X壁, 1: Y壁
}				t_ray;

typedef struct s_player
{
	double px; // プレイヤーのX座標
	double py; // プレイヤーのY座標
	// double dir_x;   // 向きのX成分
	// double dir_y;   // 向きのY成分
	double		ang;
	bool		facing_right;
	bool		facing_up;
	// double plane_x; // カメラ平面X成分
	// double plane_y; // カメラ平面Y成分
}				t_player;

typedef struct s_all
{
	t_map		map[1];
	t_ray		ray[1];
	t_player	player[1];
	void		*mlx;
	void		*mlx_win;
	void		*map_no;
	void		*map_so;
	void		*map_we;
	void		*map_ea;
}				t_all;

//init.c
t_map *init_map(void);
void parse_cub_file(char *filename, t_map *map);


#endif
