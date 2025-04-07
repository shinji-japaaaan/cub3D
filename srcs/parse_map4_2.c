/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/07 22:00:37 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_comma(char *line, int *i)
{
	if (line[*i] != ',')
		exit(printf("Error: Invalid color format\n"));
	(*i)++;
}

static void	check_color_range(int value)
{
	if (value < 0 || value > 255)
		exit(printf("Error: RGB values out of range\n"));
}

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && str[i] != ',' && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_color_value(char *line, int *i)
{
	int	len;

	char buffer[4];
	while (line[*i] == ' ')
		(*i)++;
	len = 0;
	while (ft_isdigit(line[*i]) && len < 3)
		buffer[len++] = line[(*i)++];
	buffer[len] = '\0';
	if (!is_digit_str(buffer))
		exit(printf("Error: Invalid RGB format\n"));
	return (ft_atoi(buffer));
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
		exit(printf("Error: Too many RGB values\n"));
}

static int	parse_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	skip_spaces(line, &i);
	r = parse_color_value(line, &i);
	skip_spaces(line, &i);
	check_comma(line, &i);
	skip_spaces(line, &i);
	g = parse_color_value(line, &i);
	skip_spaces(line, &i);
	check_comma(line, &i);
	skip_spaces(line, &i);
	b = parse_color_value(line, &i);
	check_color_range(r);
	check_color_range(g);
	check_color_range(b);
	validate_trailing_chars(line, i);
	return ((r << 16) | (g << 8) | b);
}

static void	validate_texture_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm", 4) != 0)
	{
		free(path);
		perror("Error: Invalid texture file format (expected .xpm)");
		exit(1);
	}
}

static void	validate_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		perror("Error: Texture file does not exist");
		exit(1);
	}
	close(fd);
}

static char	*parse_texture(char *line)
{
	char	*texture_path;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		perror("Error: Missing texture path");
		exit(1);
	}
	texture_path = ft_strdup(&line[i]);
	if (!texture_path)
	{
		perror("Error: Memory allocation failed for texture path");
		exit(1);
	}
	validate_texture_path(texture_path);
	validate_texture_file(texture_path);
	return (texture_path);
}

void	process_texture_lines(char *line, t_map *map)
{
	if (strncmp(line, "NO ", 3) == 0)
		map->tex_no = parse_texture(line);
	else if (strncmp(line, "SO ", 3) == 0)
		map->tex_so = parse_texture(line);
	else if (strncmp(line, "WE ", 3) == 0)
		map->tex_we = parse_texture(line);
	else if (strncmp(line, "EA ", 3) == 0)
		map->tex_ea = parse_texture(line);
	else if (line[0] == 'F')
		map->floor_color = parse_color(line);
	else if (line[0] == 'C')
		map->ceil_color = parse_color(line);
}
