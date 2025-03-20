/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:56:01 by karai             #+#    #+#             */
/*   Updated: 2025/03/20 21:32:39 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main()
{
	t_all all[1];
	double angle = 46;

	char* grid[] = {
		"1111111",
		"1000001",
		"1000001",
		"1000001",
		"1111111"
	};
	all->map->grid = (char**)malloc(sizeof(char*) * 6);
	for (int i = 0; i<5; i ++)
	{
		all->map->grid[i] = (char*)malloc(sizeof(char) * 10);
		all->map->grid[i] = strdup(grid[i]);
		printf("%s\n", all->map->grid[i]);
	}
	all->player->px = TILE_SIZE * 3 + 16;
	all->player->py = TILE_SIZE * 2 + 16;
	all->map->width = 7;
	all->map->height = 5;
	printf("px py %lf %lf", all->player->px, all->player->py);
	printf("horz %lf\n",horz_dist(all, angle));
	printf("vert %lf\n",vert_dist(all, angle));
}
