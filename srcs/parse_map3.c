/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/19 10:49:40 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_tex_path(char *line, t_flags *f)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_flag(&f->has_no, &f->error_flag);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_flag(&f->has_so, &f->error_flag);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_flag(&f->has_we, &f->error_flag);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_flag(&f->has_ea, &f->error_flag);
}

static void	check_colors(char *line, t_flags *f)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		set_flag(&f->has_floor, &f->error_flag);
	else if (ft_strncmp(line, "C ", 2) == 0)
		set_flag(&f->has_ceiling, &f->error_flag);
}

static int	check_map(char *line)
{
	int	has_wall;

	has_wall = (ft_strchr(line, '1') != NULL);
	return (has_wall);
}

static void	check_lines(char **lines, t_flags *f)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (check_map(lines[i]))
			f->has_map = 1;
		check_tex_path(lines[i], f);
		check_colors(lines[i], f);
		if (f->has_no && f->has_so && f->has_we && f->has_ea)
			f->has_config = 1;
		i++;
	}
}

int	validate_cub_format(char **lines)
{
	t_flags	f;

	init_flags(&f);
	check_lines(lines, &f);
	if (f.error_flag || !f.has_map || !f.has_config || !f.has_floor
		|| !f.has_ceiling)
		return (0);
	return (1);
}
