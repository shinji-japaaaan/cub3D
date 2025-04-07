/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/07 21:50:01 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error_and_exit(char *message)
{
	printf("%s", message);
	exit(EXIT_FAILURE);
}

static void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	**parse_map(char **lines, int start, int height)
{
	char	**map;
	int		i;

	// メモリ確保
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		free_lines(lines);
		print_error_and_exit("Error: Memory allocation failed\n");
	}
	i = 0;
	while (i < height)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
		{
			free_lines(lines);
			free_map(map, i);
			print_error_and_exit("Error: Memory allocation failed\n");
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	*ft_strnew(size_t size)
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

static void	fill_map_with_spaces(char **map, int map_height, int max_width)
{
	int	i;
	int	current_length;

	i = 0;
	while (i < map_height)
	{
		current_length = ft_strlen(map[i]);
		if (current_length < max_width)
		{
			map[i] = ft_strjoin(map[i], ft_strnew(max_width - current_length));
		}
		i++;
	}
}

// 最大幅を決定する関数
static int	get_max_line_width(char **lines)
{
	int	i;
	int	max_width;
	int	line_length;

	max_width = 0;
	i = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	return (max_width);
}

int	find_map_start_index(char **lines)
{
	int		i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
		{
			i++;
			continue ;
		}
		if (!(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
				line[0] == 'F' || line[0] == 'C'))
			break ;
		i++;
	}
	return (i);
}


static void	count_map_height(char **lines, int start, int *height)
{
	*height = 0;
	while (lines[start])
	{
		if (lines[start][0] != '\0')
			(*height)++;
		start++;
	}
}

static void	process_textures(char **lines, int map_start, t_map *map)
{
	int	j;

	j = 0;
	while (j < map_start)
	{
		process_texture_lines(lines[j], map);
		j++;
	}
}

void	process_lines(char **lines, t_map *map)
{
	int	map_start;
	int	map_height;
	int	map_width;

	map_start = find_map_start_index(lines);
	count_map_height(lines, map_start, &map_height);
	map->grid = parse_map(lines, map_start, map_height);
	map_width = get_max_line_width(&lines[map_start]);
	fill_map_with_spaces(map->grid, map_height, map_width);
	map->height = map_height;
	map->width = map_width;
	process_textures(lines, map_start, map);
}
