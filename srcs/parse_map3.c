/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:22:58 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_map(char *line)
{
	return (ft_strchr(line, '1') != NULL);
}

static void	check_config(char *line, int *has_no, int *has_so, int *has_we,
		int *has_ea)
{
	if (strncmp(line, "NO ", 3) == 0)
		*has_no = 1;
	if (strncmp(line, "SO ", 3) == 0)
		*has_so = 1;
	if (strncmp(line, "WE ", 3) == 0)
		*has_we = 1;
	if (strncmp(line, "EA ", 3) == 0)
		*has_ea = 1;
}

static int	check_floor(char *line)
{
	return (strncmp(line, "F ", 2) == 0);
}

static int	check_ceiling(char *line)
{
	return (strncmp(line, "C ", 2) == 0);
}

int	validate_cub_format(char **lines)
{
	int	has_map;
	int	has_config;
	int	has_floor;
	int	has_ceiling;
	int	has_no;
    int has_so; 
    int has_we;
    int has_ea;
	int	i;

	has_map = 0;
	has_config = 0;
	has_floor = 0;
	has_ceiling = 0;
	has_no = 0;
    has_so = 0; 
    has_we = 0;
    has_ea = 0;
	i = 0;
	while (lines[i])
	{
		if (check_map(lines[i]))
			has_map = 1;
		check_config(lines[i], &has_no, &has_so, &has_we, &has_ea);
		if (has_no && has_so && has_we && has_ea)
			has_config = 1;
		if (check_floor(lines[i]))
			has_floor = 1;
		if (check_ceiling(lines[i]))
			has_ceiling = 1;
		i++;
	}
	if (!has_map || !has_config || !has_floor || !has_ceiling)
		return (0);
	return (1);
}
