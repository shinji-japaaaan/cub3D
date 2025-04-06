/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/07 05:42:35 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error_and_exit(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

static void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	**parse_map(char **lines, int start, int height)
{
	char	**map;
	int		i;

	// メモリ確保
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		free_lines(lines);
		print_error_and_exit("Error: Memory allocation failed\n");
	}
	i = 0;
	// マップをコピー
	while (i < height)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
		{
			free_lines(lines);
			free_map(map, i);
			print_error_and_exit("Error: Memory allocation failed\n");
		}
		i++;
	}
	map[i] = NULL; // NULL 終端
	return (map);
}

char *ft_strnew(size_t size)
{
    char *str;

    // size + 1 のサイズを確保 (終端文字 '\0' を含めるため)
    str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL)
    {
        return NULL;  // メモリ確保に失敗した場合は NULL を返す
    }

    // 文字列のすべての文字を空白で埋める
    ft_memset(str, ' ', size);

    // 最後に終端文字 '\0' を追加
    str[size] = '\0';

    return str;
}

// マップの各行の幅を最大幅に合わせてスペースを埋める
static void	fill_map_with_spaces(char **map, int map_height, int max_width)
{
	int i;
	int current_length;

	i = 0;
	while (i < map_height)
	{
		current_length = ft_strlen(map[i]);
		if (current_length < max_width)
		{
			// 末尾にスペースを埋める
			map[i] = ft_strjoin(map[i], ft_strnew(max_width - current_length));
		}
		i++;
	}
}

// 最大幅を決定する関数
static int	get_max_line_width(char **lines)
{
	int i;
	int max_width = 0;
	int line_length;

	i = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	return (max_width);
}

int find_map_start_index(char **lines)
{
	int i = 0;

	while (lines[i])
	{
		char *line = lines[i];

		// 行頭の空白をスキップ
		while (*line == ' ' || *line == '\t')
			line++;

		// 空行はスキップ
		if (*line == '\0')
		{
			i++;
			continue;
		}

		// 設定行でなければ、それ以降はマップ
		if (!(strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
			  strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
			  line[0] == 'F' || line[0] == 'C'))
			break;
		i++;
	}
	return i;
}

void	process_lines(char **lines, t_map *map)
{
	int map_start = find_map_start_index(lines);
	int map_height = 0;
	int i = map_start;

	// map_height を数える
	while (lines[i])
	{
		if (lines[i][0] != '\0') // 空行スキップ
			map_height++;
		i++;
	}

	map->grid = parse_map(lines, map_start, map_height);

	// map_width は全体で取得（空行も含める可能性あるので別関数の方が安全）
	int map_width = get_max_line_width(&lines[map_start]);

	fill_map_with_spaces(map->grid, map_height, map_width);

	map->height = map_height;
	map->width = map_width;

	// 設定情報だけ処理するループ（マップ以前の行だけ）
	for (int j = 0; j < map_start; j++)
		process_texture_lines(lines[j], map);
}



