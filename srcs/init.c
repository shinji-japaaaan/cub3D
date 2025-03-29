/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:39:29 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/28 20:56:54 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map *init_map(void)
{
    t_map *map;

    map = malloc(sizeof(t_map));
    if (!map)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    ft_memset(map, 0, sizeof(t_map)); // 構造体全体をゼロ初期化
    map->floor_color = -1; // 未設定時は -1
    map->ceil_color = -1;
    return (map);
}

t_game *init_game(t_map *map)
{
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
    {
        free_all(map);
        exit_with_error("malloc failed");
    }
    return (game);
}