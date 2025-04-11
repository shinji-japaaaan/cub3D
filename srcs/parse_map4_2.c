/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/11 22:40:48 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char        **alloc_map(int height)
{
        char        **map;

        map = (char **)malloc(sizeof(char *) * (height + 1));
        if (!map)
                return (NULL);
        map[height] = NULL;
        return (map);
}

static void        copy_map_lines(char **dst, char **src, int start, int height)
{
        int        i;

        i = 0;
        while (i < height)
        {
                dst[i] = ft_strdup(src[start + i]);
                if (!dst[i])
                        break ;
                i++;
        }
        if (i != height)
        {
                free_lines(src);
                free_map(dst, i);
                print_error_and_exit("Error: Memory allocation failed\n");
        }
}

char        **parse_map(char **lines, int start, int height)
{
        char        **map;

        map = alloc_map(height);
        if (!map)
        {
                free_lines(lines);
                print_error_and_exit("Error: Memory allocation failed\n");
        }
        copy_map_lines(map, lines, start, height);
        return (map);
}
