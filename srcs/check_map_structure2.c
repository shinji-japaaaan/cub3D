/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/28 08:02:28 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//マップが壁（1）に囲まれているかチェック
int check_closed_walls(char **map)
{
    int i, j;
    int width, height;

    height = 0;
    while (map[height])
        height++;
    width = ft_strlen(map[0]);
    // 上下の壁チェック
    j = 0;
    while (j < width)
    {
        if (map[0][j] != '1' || map[height - 1][j] != '1')
            return (0);
        j++;
    }
    // 左右の壁チェック
    i = 0;
    while (i < height)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

//壁の外側が不完全な場合（壊れている外壁を検出）
static int check_top_bottom_walls(char **map, int width, int height)
{
    int j;

    j = 0;
    while (j < width)
    {
        if (map[0][j] != '1' || map[height - 1][j] != '1')
            return (0);
        j++;
    }
    return (1);
}

static int check_left_right_walls(char **map, int width, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

int check_incomplete_outer_wall(char **map)
{
    int width, height;

    height = 0;
    while (map[height])  // マップの高さを取得
        height++;
    width = ft_strlen(map[0]);  // マップの幅を取得

    if (!check_top_bottom_walls(map, width, height))
        return (0);  // 上下の外壁が壊れている場合
    if (!check_left_right_walls(map, width, height))
        return (0);  // 左右の外壁が壊れている場合

    return (1);
}
