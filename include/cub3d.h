/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:25:20 by karai             #+#    #+#             */
/*   Updated: 2025/03/29 09:45:49 by sishizaw         ###   ########.fr       */
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
	void	*img;
	t_map	*map;
	int		img_width;
	int		img_height;
}			t_game;

//init.c
t_map		*init_map(void);
t_game		*init_game(t_map *map);
void		start_game(t_game *game, t_map *map);
void		cleanup_and_exit(t_game *game, int exit_code);

//parse_map.c
char		**read_lines(const char *filename);
char		*read_line(int fd);
void		handle_file_read_error(void);
void		handle_invalid_cub_format(void);
int			validate_cub_format(char **lines);
void		process_lines(char **lines, t_map *map);
void		print_error_and_exit(char *message);
void		process_texture_lines(char *line, t_map *map);

//check_map_content.c
int			check_map_content(char **map);
int			check_surroundings(char **map);
int			check_player_start_position(char **map);
int			error(char *msg);

//check_map_structure.c
int			check_map_structure(char **map);
int			check_closed_walls(char **map);
int			check_incomplete_outer_wall(char **map);

//free.c
void		free_all(t_map *map);
void		exit_with_error(char *msg);
void		free_lines(char **lines);

#endif
