/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/07 21:13:47 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_map(char *line)
{
	return (ft_strchr(line, '1') != NULL);
}

static void	check_config(char *line, int *has_no, int *has_so, int *has_we,
		int *has_ea, int *has_floor, int *has_ceiling, int *error_flag)
{
	if (strncmp(line, "NO ", 3) == 0)
	{
		if (*has_no)
			*error_flag = 1; // "NO"が2回以上の場合はエラー
		*has_no = 1;
	}
	if (strncmp(line, "SO ", 3) == 0)
	{
		if (*has_so)
			*error_flag = 1; // "SO"が2回以上の場合はエラー
		*has_so = 1;
	}
	if (strncmp(line, "WE ", 3) == 0)
	{
		if (*has_we)
			*error_flag = 1; // "WE"が2回以上の場合はエラー
		*has_we = 1;
	}
	if (strncmp(line, "EA ", 3) == 0)
	{
		if (*has_ea)
			*error_flag = 1; // "EA"が2回以上の場合はエラー
		*has_ea = 1;
	}
	if (strncmp(line, "F ", 2) == 0)
	{
		if (*has_floor)
			*error_flag = 1; // "F"が2回以上の場合はエラー
		*has_floor = 1;
	}
	if (strncmp(line, "C ", 2) == 0)
	{
		if (*has_ceiling)
			*error_flag = 1; // "C"が2回以上の場合はエラー
		*has_ceiling = 1;
	}
}

int	validate_cub_format(char **lines)
{
	int	has_map;
	int	has_config;
	int	has_floor;
	int	has_ceiling;
	int	has_no;
	int	has_so;
	int	has_we;
	int	has_ea;
	int	i;

	int error_flag; // エラーフラグ
	has_map = 0;
	has_config = 0;
	has_floor = 0;
	has_ceiling = 0;
	has_no = 0;
	has_so = 0;
	has_we = 0;
	has_ea = 0;
	error_flag = 0; // 初期化
	i = 0;
	while (lines[i])
	{
		if (check_map(lines[i]))
			has_map = 1;
		check_config(lines[i], &has_no, &has_so, &has_we, &has_ea, &has_floor,
				&has_ceiling, &error_flag);
		if (has_no && has_so && has_we && has_ea)
			has_config = 1;
		i++;
	}
	// エラーがあれば0を返す
	if (error_flag || !has_map || !has_config || !has_floor || !has_ceiling)
		return (0);
	return (1);
}
