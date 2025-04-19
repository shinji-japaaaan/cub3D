/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:49:44 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static char	*fill_line_with_spaces(char *line, int max_width)
{
	int		current_length;
	char	*spaces;
	char	*new_line;

	current_length = ft_strlen(line);
	if (current_length >= max_width)
		return (line);
	spaces = ft_strnew(max_width - current_length);
	if (!spaces)
		return (NULL);
	new_line = ft_strjoin(line, spaces);
	free(spaces);
	if (!new_line)
		return (NULL);
	free(line);
	return (new_line);
}

int	fill_map_with_spaces(char **grid, int map_height, int max_width)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < map_height)
	{
		new_line = fill_line_with_spaces(grid[i], max_width);
		if (!new_line)
			return (0);
		grid[i] = new_line;
		i++;
	}
	return (1);
}
