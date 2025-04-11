/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:11:37 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	process_texture_lines(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->tex_no = parse_texture(line);//parse_texture内での各種free処理が必要かも
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->tex_so = parse_texture(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->tex_we = parse_texture(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->tex_ea = parse_texture(line);
	else if (line[0] == 'F')
		map->floor_color = parse_color(line);//parse_color内での各種free処理が必要かも
	else if (line[0] == 'C')
		map->ceil_color = parse_color(line);
}

void	process_textures(char **lines, int map_start, t_map *map)
{
	int	j;

	j = 0;
	while (j < map_start)
	{
		process_texture_lines(lines[j], map);
		j++;
	}
}

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	ft_memset(str, ' ', size);
	str[size] = '\0';
	return (str);
}

void	fill_map_with_spaces(char **map, int map_height, int max_width)
{
	int	i;
	int	current_length;

	i = 0;
	while (i < map_height)
	{
		current_length = ft_strlen(map[i]);
		if (current_length < max_width)
		{
			map[i] = ft_strjoin(map[i], ft_strnew(max_width - current_length));//失敗したときの処理
		}
		i++;
	}
}
