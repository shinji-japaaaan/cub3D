/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/04/19 16:30:06 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_MAP_HEIGHT 100
# define MAX_MAP_WIDTH 100
# define BUFFER_SIZE 1024
# define TILE_SIZE 32
# define WIND_HEIGHT 960
# define WIND_WIDTH 1280
# define FOV_ANGLE 60
# define SCALE 0.8
# define DT 30
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

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*tex_no_img;
	void			*tex_so_img;
	void			*tex_ea_img;
	void			*tex_we_img;
	t_map			*map;
	int				img_width;
	int				img_height;
}					t_game;

typedef struct s_flags
{
	int				has_no;
	int				has_so;
	int				has_we;
	int				has_ea;
	int				has_floor;
	int				has_ceiling;
	int				has_map;
	int				has_config;
	int				error_flag;
}					t_flags;

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
	int				width;
	int				height;
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
	double			dpp;
	t_xpm			xpm_no[1];
	t_xpm			xpm_so[1];
	t_xpm			xpm_we[1];
	t_xpm			xpm_ea[1];
	long long		last_scan;
	struct timeval	tv;
	double			ray_angle;
	double			wall_strip_height;
	double			offset;
	int				stop;
}					t_all;

// main.c
void				loop_function(t_all *all);

// init.c
char				**init_lines(int *capacity);
void				init_map(t_map *map);
t_game				*init_game(t_map *map);
void				init_flags(t_flags *f);
void				start_game(t_game *game, t_map *map);

// parse_map.c
char				**read_lines(const char *filename);
int					read_chars(int fd, char *buffer);
char				**handle_resize(char **lines, int *cap, char *line, int fd);
int					validate_cub_format(char **lines);

// parse_map4.c
void				process_lines(char **lines, t_map *map);
int					fill_map_with_spaces(char **grid, int map_height,
						int max_width);
void				parse_config_lines(char **lines, int map_start, t_map *map);
int					parse_texture_safe(char *line, char **out_path);
int					parse_color_safe(char *line, int *out_color);
int					find_map_start_index(char **lines);
void				get_max_line_width(char **lines, int *width);
int					check_color_range(int value);
void				count_map_height(char **lines, int start, int *height);
void				check_map_height(char **lines, int height);
void				check_map_width(char **lines, int width);
int					check_comma(char *line, int *i);
int					parse_color_value(char *line, int *i);

void				set_flag(int *flag, int *error);
void				print_error_and_exit(char *message);
void				print_perror_and_exit(char *message);
int					error(char *msg);

// check_map_content.c
int					check_map_content(t_map *map);

// check_map_structure.c
int					check_map_structure(t_map *map);
int					check_outer_wall(t_map *map);

// free.c
void				free_all(t_map *map);
void				exit_with_error(char *msg);
void				free_lines(char **lines);
void				free_map(char **map, int size);

void				print_map(t_map *map);

// utility_mix.c
void				initialize_window(t_all *all);
void				initialize_all(t_all *all);
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
void				put_backview(t_all *all, int floor_color, int ceil_color);
void				put_waltexture(t_all *all, int i);

// init_mlx.c
void				init_player(t_map *map, t_player *player);
void				start_pos(t_map *map, t_player *player, size_t i, size_t j);

// update.c

void				update(t_all *all, t_player *player);

// update_utils.c
bool				is_wall_inside(t_all *all, double x, double y);

// key_hook.c
int					map_close(t_all *all);
int					ft_key_release(int keycode, t_all *all);
int					ft_key_press(int keycode, t_all *all);

// put_vd.c
int					get_img_horz_idx_v(t_all *all, double dist, t_xpm *xpm_var);
void				put_1line_case_vd(t_all *all, int i, double vd);
void				put_1line_vert(t_all *all, int i, double dist,
						t_xpm *xpm_var);

// put_hd.c
int					get_img_horz_idx_h(t_all *all, double dist, t_xpm *xpm_var);
void				put_1line_case_hd(t_all *all, int i, double hd);
void				put_1line_horz(t_all *all, int i, double dist,
						t_xpm *xpm_var);

// destroy_all.c
void				destroy_all(t_all *all);

#endif
