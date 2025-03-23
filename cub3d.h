/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/03/23 10:25:08 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define TILE_SIZE 30
# define WIND_HEIGHT 480
# define WIND_WIDTH 640
# define FOV_ANGLE 60
# define SCALE 0.8
# define M_PI 3.14159265358979323846
# define M_2PI   6.28318530717958623199
#define M_1by2PI 1.57079632679489655799
#define M_3by2PI 4.71238898038468967399

# define TURN_LEFT -1
# define TURN_RIGHT 1
# define MOVE_FRONT 1
# define MOVE_LEFT 2
# define MOVE_BACK 3
# define MOVE_RIGHT 4

# define UP_ARROW 65362
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define ESCAPE 65307
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3

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
	int			wind_width;
	int			wind_height;
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
	int			turnDirection;
	int			walkDirection;
	double		moveSpeed;
	double		rotSpeed;

	// double plane_x; // カメラ平面X成分
	// double plane_y; // カメラ平面Y成分
}				t_player;

typedef struct s_img
{
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_all
{
	t_map		map[1];
	t_ray		ray[1];
	t_player	player[1];
	t_img		img;
	void		*mlx;
	void		*mlx_win;
	void		*map_no;
	void		*map_so;
	void		*map_we;
	void		*map_ea;
	double		dPP;
}				t_all;

// utility_mix.c
void			initialize_window(t_all *all);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				map_close(t_all *all);
int				ft_key_hook(int keycode, t_all *all);
int				ft_key_release(int keycode, t_all *all);
int				ft_key_press(int keycode, t_all *all);

// hit_utils.c
double			cnv_rad(double angle);
bool			is_out_map(t_all *all, int hit_ij[2]);
bool			is_wall(t_all *all, int hit_ij[2]);
double			normalize_rad(double x);

// hit_horz.c
void			get_map_horz_idx(double Ax, double Ay, double angle,
					int hit_ij[2]);
double			horz_dist(t_all all[1], double angle);

// hit_vert.c
void			get_map_vert_idx(double Ax, double Ay, double angle,
					int hit_ij[2]);
double			vert_dist(t_all all[1], double angle);

// img_raycast.c
void			img_raycast(t_all *all);

// init.c
void			init_player(t_player *player);
void			init_map(t_map *map);

// update.c
bool			is_WallInside(t_all *all, double x, double y);
void			update(t_all *all, t_player *player);

#endif
