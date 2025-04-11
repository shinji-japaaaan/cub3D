/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/12 07:11:02 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_comma(char *line, int *i)
{
	if (line[*i] != ',')
		print_error_and_exit("Error: Invalid color format\n");
	(*i)++;
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

static void	validate_trailing_chars(char *line, int i)
{
	skip_spaces(line, &i);
	if (line[i] != '\0')
		print_error_and_exit("Error: Too many RGB values\n");
}

static int	get_next_color(char *line, int *i, int need_comma)
{
	int	value;

	skip_spaces(line, i);
	if (need_comma)
		check_comma(line, i);
	skip_spaces(line, i);
	value = parse_color_value(line, i);
	return (value);
}

int	parse_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	r = get_next_color(line, &i, 0);
	g = get_next_color(line, &i, 1);
	b = get_next_color(line, &i, 1);
	check_color_range(r);
	check_color_range(g);
	check_color_range(b);
	validate_trailing_chars(line, i);
	return ((r << 16) | (g << 8) | b);
}