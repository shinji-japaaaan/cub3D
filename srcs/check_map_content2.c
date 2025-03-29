/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/29 09:15:52 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//床 (0) やプレイヤー (N, S, E, W) の周囲が閉じているか
static int	is_valid_position(char c)
{
	return (c == '0' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W');
}

static int	is_surrounded(char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || !map[y + 1] || !map[y][x + 1])
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	check_surroundings(char **map)
{
	int i, j;
	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (is_valid_position(map[i][j]) && !is_surrounded(map, j, i))
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

int	check_player_start_position(char **map)
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