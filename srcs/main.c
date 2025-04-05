/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:10:04 by sishizaw          #+#    #+#             */
/*   Updated: 2025/04/05 10:12:11 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_cub_file(const char *filename, t_map *map)
{
	char	**lines;

	lines = read_lines(filename);
	if (!lines)
		handle_file_read_error();
	if (!validate_cub_format(lines))
	{
		free_lines(lines);
		handle_invalid_cub_format();
	}
	process_lines(lines, map);
	free_lines(lines);
}

static int validate_map(t_map *map)
{
    if (!check_map_structure(map))
    {
        free_all(map);
        exit_with_error("Invalid map format");
    }
    else if (!check_map_content(map))
    {
        free_all(map);
        exit_with_error("Invalid map format");
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_map *map;
    t_game *game;

    if (argc != 2) {
        printf("Error: You must provide exactly two .cub files.\n");
        exit(1);
    }
    map = init_map();
    parse_cub_file(argv[1], map);//プレイヤーの位置が二つある場合、エラー
    validate_map(map);
    game = init_game(map);
    start_game(game, map);
    free_all(map);
    cleanup_and_exit(game, EXIT_SUCCESS);
}