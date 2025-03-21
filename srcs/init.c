/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/21 13:47:33 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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