/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:03:55 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/23 13:13:54 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_all(t_map *map)
{
    int i = 0;

    while (i < map->height)
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
    if (map->tex_no)
        free(map->tex_no);
    if (map->tex_so)
        free(map->tex_so);
    if (map->tex_we)
        free(map->tex_we);
    if (map->tex_ea)
        free(map->tex_ea);
    free(map);
}

void exit_with_error(t_map *map, char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	free_all(map);  // ここでメモリ解放
	exit(EXIT_FAILURE);  // エラー終了
}

