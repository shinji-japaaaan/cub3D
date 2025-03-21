/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:10:04 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/21 12:25:30 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_map *init_map(void)
{
    t_map *map;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->tex_no = NULL;
    map->tex_so = NULL;
    map->tex_we = NULL;
    map->tex_ea = NULL;
    map->floor_color = -1; // 未設定時は -1
    map->ceil_color = -1;
    return (map);
}

int main(void)
{
    t_map *map;

    map = init_map();
    if (!map)
    {
        printf("Error: Failed to initialize map.\n");
        return (1);
    }
    
    // 初期化が正しく行われたか確認
    printf("Map initialized:\n");
    printf("Width: %d, Height: %d\n", map->width, map->height);
    printf("Textures: NO=%p, SO=%p, WE=%p, EA=%p\n",
           (void *)map->tex_no, (void *)map->tex_so,
           (void *)map->tex_we, (void *)map->tex_ea);
    printf("Floor Color: %d, Ceiling Color: %d\n",
           map->floor_color, map->ceil_color);

    // メモリ解放
    free(map);
    return (0);
}

