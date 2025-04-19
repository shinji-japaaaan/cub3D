/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:49:48 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_config_line(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_safe(line, &map->tex_no));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_safe(line, &map->tex_so));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_safe(line, &map->tex_we));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_safe(line, &map->tex_ea));
	else if (line[0] == 'F')
		return (parse_color_safe(line, &map->floor_color));
	else if (line[0] == 'C')
		return (parse_color_safe(line, &map->ceil_color));
	return (0);
}

void	parse_config_lines(char **lines, int map_start, t_map *map)
{
	int	j;
	int	status;

	j = 0;
	while (j < map_start)
	{
		status = handle_config_line(lines[j], map);
		if (status == -1)
		{
			free_lines(lines);
			free_all(map);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}
