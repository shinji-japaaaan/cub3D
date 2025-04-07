/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/07 21:14:00 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_comma(char *line, int *i)
{
	if (line[*i] != ',')
		exit(printf("Error: Invalid color format\n"));
	(*i)++;
}

static void	check_color_range(int value)
{
	if (value < 0 || value > 255)
		exit(printf("Error: RGB values out of range\n"));
}

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && str[i] != ',' && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_color_value(char *line, int *i)
{
	int	len;

	char buffer[4]; // RGBは最大3桁＋null終端
	while (line[*i] == ' ')
		(*i)++;
	len = 0;
	while (ft_isdigit(line[*i]) && len < 3)
		buffer[len++] = line[(*i)++];
	buffer[len] = '\0';
	if (!is_digit_str(buffer))
		exit(printf("Error: Invalid RGB format\n"));
	return (ft_atoi(buffer));
}

static int	parse_color(char *line)
{
	int	i;

	i = 1;
	int r, g, b;
	while (line[i] == ' ')
		i++;
	r = parse_color_value(line, &i);
	while (line[i] == ' ')
		i++;
	check_comma(line, &i);
	while (line[i] == ' ')
		i++;
	g = parse_color_value(line, &i);
	while (line[i] == ' ')
		i++;
	check_comma(line, &i);
	while (line[i] == ' ')
		i++;
	b = parse_color_value(line, &i);
	check_color_range(r);
	check_color_range(g);
	check_color_range(b);
	// 残りにゴミがあればエラー
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		exit(printf("Error: Too many RGB values\n"));
	return ((r << 16) | (g << 8) | b);
}

static char	*parse_texture(char *line)
{
	char	*texture_path;
	int		i;
	int		fd;

	i = 2;
	// 空白文字をスキップ
	while (line[i] == ' ')
		i++;
	// テクスチャパスが空でないかを確認
	if (line[i] == '\0')
	{
		perror("Error: Missing texture path");
		exit(1);
	}
	// テクスチャパスのコピー
	texture_path = strdup(&line[i]);
	if (!texture_path)
	{
		perror("Error: Memory allocation failed for texture path");
		exit(1);
	}
	// ファイル拡張子のチェック
	if (strncmp(&texture_path[strlen(texture_path) - 4], ".xpm", 4) != 0)
	{
		free(texture_path);
		perror("Error: Invalid texture file format (expected .xpm)");
		exit(1);
	}
	// open関数でファイルを開く（読み取り専用）
	fd = open(texture_path, O_RDONLY);
	if (fd == -1) // ファイルが存在しない場合
	{
		free(texture_path);
		perror("Error: Texture file does not exist");
		exit(1);
	}
	// ファイルが開けた場合は閉じる
	close(fd);
	return (texture_path);
}

void	process_texture_lines(char *line, t_map *map)
{
	if (strncmp(line, "NO ", 3) == 0)
		map->tex_no = parse_texture(line);
	else if (strncmp(line, "SO ", 3) == 0)
		map->tex_so = parse_texture(line);
	else if (strncmp(line, "WE ", 3) == 0)
		map->tex_we = parse_texture(line);
	else if (strncmp(line, "EA ", 3) == 0)
		map->tex_ea = parse_texture(line);
	else if (line[0] == 'F')
		map->floor_color = parse_color(line);
	else if (line[0] == 'C')
		map->ceil_color = parse_color(line);
}
