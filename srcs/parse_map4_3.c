/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:49:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		if (!(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
				|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
					3) == 0 || line[0] == 'F' || line[0] == 'C'))
			break ;
		i++;
	}
	return (i);
}

void	get_max_line_width(char **lines, int *width)
{
	int	i;
	int	line_length;
	int	max_width;

	max_width = 0;
	i = 0;
	while (lines[i])
	{
		line_length = ft_strlen(lines[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	*width = max_width;
}

void	count_map_height(char **lines, int start, int *height)
{
	*height = 0;
	while (lines[start])
	{
		(*height)++;
		start++;
	}
}

void	check_map_height(char **lines, int height)
{
	if (height > MAX_MAP_HEIGHT)
	{
		free_lines(lines);
		print_error_and_exit("Error: Map height exceeds 100 lines\n");
	}
}

void	check_map_width(char **lines, int width)
{
	if (width > MAX_MAP_WIDTH)
	{
		free_lines(lines);
		print_error_and_exit("Error: Map width exceeds 100 columns\n");
	}
}
