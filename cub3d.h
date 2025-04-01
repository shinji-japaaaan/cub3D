/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/04/01 23:24:29 by karai            ###   ########.fr       */
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
# include <sys/time.h>

# define TILE_SIZE 30
# define IMG_SIZE 640
# define WIND_HEIGHT 480
# define WIND_WIDTH 640
# define FOV_ANGLE 60
# define SCALE 0.8
# define DT 50
# define STEP_SPEED 0.5
# define STEP_ANGLE 0.5
# define M_PI 3.14159265358979323846
# define M_TWO_PI 6.28318530717958623199
# define M_ONETWO_PI 1.57079632679489655799
# define M_THREETWO_PI 4.71238898038468967399

# define TURN_LEFT 1
# define TURN_RIGHT -1
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
	char			**grid;
	int				width;
	int				height;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	int				floor_color;
	int				ceil_color;
	int				wind_width;
	int				wind_height;
}					t_map;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			delta_x;
	double			delta_y;
	int				map_x;
	int				map_y;
	int				side;
}					t_ray;

typedef struct s_player
{
	double			px;
	double			py;

	double			ang;
	bool			facing_right;
	bool			facing_up;
	int				turn_direction;
	int				walk_direction;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_xpm
{
	void			*map;
	void			*addr;
	int				line_length;
	int				endian;
	int				bpp;
}					t_xpm;

typedef struct s_img
{
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_all
{
	t_map			map[1];
	t_ray			ray[1];
	t_player		player[1];
	t_img			img;
	void			*mlx;
	void			*mlx_win;
	double			dPP;
	t_xpm			xpm_no[1];
	t_xpm			xpm_so[1];
	t_xpm			xpm_we[1];
	t_xpm			xpm_ea[1];
	long long		last_scan;
	struct timeval	tv;
	double			ray_angle;
	double			wallStripHeight;
	int				offset;
	int				stop;
}					t_all;

// utility_mix.c
void				initialize_window(t_all *all);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int					my_mlx_pixel_get(t_xpm *xpm, int x, int y);

// hit_utils.c
double				cnv_rad(double angle);
bool				is_out_map(t_all *all, int hit_ij[2]);
bool				is_wall(t_all *all, int hit_ij[2]);
double				normalize_rad(double x);

// hit_horz.c
void				get_map_horz_idx(double Ax, double Ay, double angle,
						int hit_ij[2]);
double				horz_dist(t_all all[1], double angle);

// hit_vert.c
void				get_map_vert_idx(double Ax, double Ay, double angle,
						int hit_ij[2]);
double				vert_dist(t_all all[1], double angle);

// img_raycast.c
void				img_raycast(t_all *all);

// init.c
void				init_player(t_player *player);
void				init_map(t_map *map);

// update.c

void				update(t_all *all, t_player *player);

// update_utils.c
bool				is_wall_inside(t_all *all, double x, double y);

// key_hook.c
int					map_close(t_all *all);
int					ft_key_release(int keycode, t_all *all);
int					ft_key_press(int keycode, t_all *all);

#endif
