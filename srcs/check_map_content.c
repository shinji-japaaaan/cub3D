/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/30 19:01:11 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}

//不正な文字が含まれていないかチェック
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == ' ');
}

static int	check_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

//プレイヤー位置が存在するかチェック
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_player_start_position(char **map)
{
	int i = 0;
	int j;
	int player_found = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				if (player_found)
					return (0);
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	return (player_found);
}

int	check_map_content(t_map *map)
{
	if (!check_valid_chars(map->grid))
	{
		error("Map contains invalid characters");
		return (0);
	}
	if (!check_player_start_position(map->grid))
	{
		error("No player start position found");
		return (0);
	}
	return (1);
}
