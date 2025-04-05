/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/31 21:07:45 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//マップが壁（1）に囲まれているかチェック
static int check_closed_walls(t_map *map)
{
    int i;
    int j;
    int width;
    int height;
    char **grid;

    width = map->width;
    height = map->height;
    grid = map->grid;
    // 上下の壁チェック
    j = 0;
    while (j < width)
    {
        if (grid[0][j] != '1' || grid[height - 1][j] != '1')
            return (0);
        j++;
    }
    // 左右の壁チェック
    i = 0;
    while (i < height)
    {
        if (grid[i][0] != '1' || grid[i][width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

// すべてのチェックを統合してマップを検証
int check_map_structure(t_map *map)
{
    if (!check_closed_walls(map))
        return (error("Map is not surrounded by walls"));
    return (1);
}


