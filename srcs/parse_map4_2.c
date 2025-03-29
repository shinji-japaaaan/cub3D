/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:41:13 by sishizaw         ###   ########.fr       */
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

static int	parse_color_value(char *line, int *i)
{
	int	value;

	value = ft_atoi(&line[*i]);
	while (line[*i] && line[*i] != ',')
		(*i)++;
	return (value);
}

static int	parse_color(char *line)
{
	int i; // "F" または "C" の次の文字から開始
	int r;
    int g;
    int b;

    i = 1;
	// 空白をスキップ
	while (line[i] == ' ')
		i++;
	// 赤色値の取得
	r = parse_color_value(line, &i);
	check_comma(line, &i);
	// 緑色値の取得
	g = parse_color_value(line, &i);
	check_comma(line, &i);
	// 青色値の取得
	b = parse_color_value(line, &i);
	// RGB値の範囲チェック
	check_color_range(r);
	check_color_range(g);
	check_color_range(b);
	// RGBを16進数に変換して返す
	return (r << 16 | g << 8 | b);
}

static char	*parse_texture(char *line)
{
	char	*texture_path;
	int i; // "NO", "SO", "WE", "EA" の後ろからスタート

    i = 2;
	// 空白をスキップ
	while (line[i] == ' ')
		i++;
	// テクスチャパスが空でないかチェック
	if (line[i] == '\0')
		print_error_and_exit("Error: Missing texture path\n");
	// テクスチャパスをコピー
	texture_path = ft_strdup(&line[i]);
	if (!texture_path)
		print_error_and_exit("Error: Memory allocation failed for texture path\n");
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
