/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/06 20:26:48 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#include <stdio.h>

// 外側の壁チェック（1以外の文字が外側にある）
static int check_outer_wall(t_map *map)
{
    int i;
    int j;
    int width = map->width;
    int height = map->height;
    char **grid = map->grid;

    // 上下の行の外側のチェック
    for (j = 0; j < width; j++)
    {
        // 外側に '1' 以外の文字がある（スペースも許可）
        if (grid[0][j] != '1' && grid[0][j] != ' ')
        {
            printf("Error: Invalid character '%c' at top row, column %d\n", grid[0][j], j);  // デバッグ用
            return (0); // 外側に不正な文字がある
        }
        if (grid[height - 1][j] != '1' && grid[height - 1][j] != ' ')
        {
            printf("Error: Invalid character '%c' at bottom row, column %d\n", grid[height - 1][j], j);  // デバッグ用
            return (0); // 外側に不正な文字がある
        }
    }

    // 左右の列の外側のチェック
    for (i = 0; i < height; i++)
    {
        // 外側に '1' 以外の文字がある（スペースも許可）
        if (grid[i][0] != '1' && grid[i][0] != ' ')
        {
            printf("Error: Invalid character '%c' at left column, row %d\n", grid[i][0], i);  // デバッグ用
            return (0); // 外側に不正な文字がある
        }
        if (grid[i][width - 1] != '1' && grid[i][width - 1] != ' ')
        {
            printf("Error: Invalid character '%c' at right column, row %d\n", grid[i][width - 1], i);  // デバッグ用
            return (0); // 外側に不正な文字がある
        }
    }

    return (1);
}

// 1以外の文字（Nや0等）の隣にスペースがあるかチェック
static int check_adjacent_non_wall(t_map *map)
{
    int i;
    int j;
    int width = map->width;
    int height = map->height;
    char **grid = map->grid;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (grid[i][j] != '1' && grid[i][j] != ' ' ) // 1以外の文字（'N'、'0'など）
            {
                // 隣接する場所にスペースがあるかチェック
                if ((i > 0 && grid[i - 1][j] == ' ') || 
                    (i < height - 1 && grid[i + 1][j] == ' ') ||
                    (j > 0 && grid[i][j - 1] == ' ') || 
                    (j < width - 1 && grid[i][j + 1] == ' '))
                {
                    printf("Error: Character '%c' at row %d, column %d has adjacent space.\n", grid[i][j], i, j);  // デバッグ用
                    return (0); // 隣にスペースがあった場合
                }
            }
        }
    }

    return (1);
}

// マップの中身を出力する関数
static void print_map(t_map *map)
{
    int i;
    int height = map->height;
    char **grid = map->grid;

    printf("Map contents:\n");
    for (i = 0; i < height; i++)
    {
        printf("%s\n", grid[i]);  // 各行を出力
    }
    printf("\n");
}

// すべてのチェックを統合してマップを検証
int check_map_structure(t_map *map)
{
    // マップの内容を出力
    print_map(map);
    if (!check_outer_wall(map))
        return (error("Map has invalid characters at the outer walls"));

    if (!check_adjacent_non_wall(map))
        return (error("Map has adjacent non-wall characters with spaces"));

    return (1);
}









