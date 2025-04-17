/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/04/17 13:51:42 by sishizaw         ###   ########.fr       */
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
# include <unistd.h>

# define BUFFER_SIZE 1024
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define TEXTURE_PATH "./textures/wall_texture.xpm"
# define MAX_MAP_HEIGHT 100
# define MAX_MAP_WIDTH 100

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
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*tex_no_img;
	void	*tex_so_img;
	void	*tex_ea_img;
	void	*tex_we_img;
	t_map	*map;
	int		img_width;
	int		img_height;
}			t_game;

typedef struct s_flags
{
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_floor;
	int		has_ceiling;
	int		has_map;
	int		has_config;
	int		error_flag;
}			t_flags;

//init.c
char		**init_lines(int *capacity);
t_map		*init_map(void);
t_game		*init_game(t_map *map);
void		init_flags(t_flags *f);
void		start_game(t_game *game, t_map *map);

//parse_map.c
char		**read_lines(const char *filename);
int			read_chars(int fd, char *buffer);
char		**handle_resize(char **lines, int *cap, char *line, int fd);
int			validate_cub_format(char **lines);

//parse_map4.c
void		process_lines(char **lines, t_map *map);
int			fill_map_with_spaces(char **map, int map_height, int max_width);
void		parse_config_lines(char **lines, int map_start, t_map *map);
int			parse_texture_safe(char *line, char **out_path);
int			parse_color_safe(char *line, int *out_color);
int			find_map_start_index(char **lines);
void		get_max_line_width(char **lines, int *width);
int			check_color_range(int value);
void		count_map_height(char **lines, int start, int *height);
void		check_map_height(char **lines, int height);
void		check_map_width(char **lines, int width);
int			check_comma(char *line, int *i);
int			parse_color_value(char *line, int *i);

void		set_flag(int *flag, int *error);
void		print_error_and_exit(char *message);
void		print_perror_and_exit(char *message);
void		cleanup_and_exit(t_game *game, int exit_code);
int			error(char *msg);

//check_map_content.c
int			check_map_content(t_map *map);

//check_map_structure.c
int			check_map_structure(t_map *map);
int			check_outer_wall(t_map *map);

//free.c
void		free_all(t_map *map);
void		exit_with_error(char *msg);
void		free_lines(char **lines);
void		free_map(char **map, int size);

void		print_map(t_map *map);

#endif
