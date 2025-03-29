/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/28 08:06:25 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//マップが長方形かチェック
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

//壁が不規則に配置されている場合をチェック
static int get_map_dimensions(char **map, int *width, int *height)
{
    *height = 0;
    while (map[*height]) // マップの高さを取得
        (*height)++;
    *width = ft_strlen(map[0]); // マップの幅を取得
    return 0;
}

static int is_irregular_wall(int i, int j, char **map)
{
    if (map[i][j] == '1') {
        if (map[i - 1][j] != '1' && map[i + 1][j] != '1' &&
            map[i][j - 1] != '1' && map[i][j + 1] != '1')
            return (1); // 壁が隣接していない場合は不規則
    }
    return 0;
}

static int check_irregular_walls(char **map)
{
    int i, j;
    int width, height;

    get_map_dimensions(map, &width, &height);

    i = 1;
    while (i < height - 1) {
        j = 1;
        while (j < width - 1) {
            if (is_irregular_wall(i, j, map))
                return (0);  // 壁が不規則
            j++;
        }
        i++;
    }
    return (1);
}

// すべてのチェックを統合してマップを検証
int check_map_structure(char **map)
{
    if (!check_rectangular(map))
        return (error("Map is not rectangular"));
    if (!check_irregular_walls(map))
        return (error("Map contains irregularly placed walls"));
    if (!check_closed_walls(map))
        return (error("Map is not surrounded by walls"));
    if (!check_incomplete_outer_wall(map))
        return (error("Map contains incomplete outer wall"));
    return (1);
}


