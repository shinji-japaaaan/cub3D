/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:50:00 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

static int	validate_trailing_chars(char *line, int i)
{
	skip_spaces(line, &i);
	if (line[i] != '\0')
	{
		printf("Error: Too many RGB values\n");
		return (0);
	}
	return (1);
}

static int	get_next_color(char *line, int *i, int need_comma)
{
	int	value;

	skip_spaces(line, i);
	if (need_comma && !check_comma(line, i))
		return (-1);
	skip_spaces(line, i);
	value = parse_color_value(line, i);
	return (value);
}

static int	parse_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	r = get_next_color(line, &i, 0);
	g = get_next_color(line, &i, 1);
	b = get_next_color(line, &i, 1);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	if (!check_color_range(r) || !check_color_range(g) || !check_color_range(b))
		return (-1);
	if (!validate_trailing_chars(line, i))
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_color_safe(char *line, int *out_color)
{
	int	color;

	color = parse_color(line);
	if (color == -1)
		return (-1);
	*out_color = color;
	return (0);
}
