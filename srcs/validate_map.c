/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/23 13:21:43 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int error(char *msg)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (0);
}

// 1. マップが長方形かチェック
static int check_rectangular(char **map)
{
    int i;
    int width;

    if (!map || !map[0])
        return (0);
    width = ft_strlen(map[0]);
    i = 1;
    while (map[i])
    {
        if ((int)ft_strlen(map[i]) != width)
            return (0);
        i++;
    }
    return (1);
}

// 2. マップが壁（1）に囲まれているかチェック
static int check_closed_walls(char **map)
{
    int i, j;
    int width, height;

    height = 0;
    while (map[height])
        height++;
    width = ft_strlen(map[0]);

    // 上下の壁チェック
    for (j = 0; j < width; j++)
    {
        if (map[0][j] != '1' || map[height - 1][j] != '1')
            return (0);
    }

    // 左右の壁チェック
    for (i = 0; i < height; i++)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
    }
    return (1);
}

// 3. 不正な文字が含まれていないかチェック
static int check_valid_chars(char **map)
{
    int i, j;
    char c;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            c = map[i][j];
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && 
                c != 'E' && c != 'W' && c != ' ')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

// 4. 床 (0) やプレイヤー (N, S, E, W) の周囲が閉じているか
static int is_surrounded(char **map, int x, int y)
{
    if (x <= 0 || y <= 0 || !map[y + 1] || !map[y][x + 1])
        return (0);
    if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
        map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
        return (0);
    return (1);
}

static int check_surroundings(char **map)
{
    int i, j;

    i = 1;
    while (map[i + 1]) // 最初と最後の行はスキップ（すでに壁チェック済み）
    {
        j = 1;
        while (map[i][j + 1]) // 最初と最後の列はスキップ
        {
            if (map[i][j] == '0' || map[i][j] == 'N' ||
                map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (!is_surrounded(map, j, i))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

// 5. すべてのチェックを統合してマップを検証
int validate_map(char **map)
{
    if (!check_rectangular(map))
        return (error("Map is not rectangular"));
    if (!check_closed_walls(map))
        return (error("Map is not surrounded by walls"));
    if (!check_valid_chars(map))
        return (error("Map contains invalid characters"));
    if (!check_surroundings(map))
        return (error("Map contains open spaces"));
    return (1);
}
