/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/21 13:48:06 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// 空白文字をスキップ
char *skip_spaces(char *str)
{
    while (*str == ' ' || *str == '\t')
        str++;
    return (str);
}

// 文字列が特定のプレフィックスで始まっているか確認
int starts_with(char *line, char *prefix)
{
    int i = 0;
    while (prefix[i])
    {
        if (line[i] != prefix[i])
            return (0);
        i++;
    }
    return (1);
}

// テクスチャのパスを設定
void set_texture(char **dest, char *line)
{
    while (*line && *line != ' ')
        line++;
    line = skip_spaces(line);
    *dest = ft_strdup(line);
}

// RGBの色を解析
int parse_color(char *line)
{
    int r, g, b;
    r = g = b = 0;

    while (*line && (*line < '0' || *line > '9'))
        line++;
    r = ft_atoi(line);
    while (*line && *line != ',') line++;
    if (*line == ',') line++;

    g = ft_atoi(line);
    while (*line && *line != ',') line++;
    if (*line == ',') line++;

    b = ft_atoi(line);
    return ((r << 16) | (g << 8) | b);
}

// 1行を解析してデータを設定
void parse_line(t_map *map, char *line)
{
    if (starts_with(line, "NO"))
        set_texture(&map->tex_no, line + 2);
    else if (starts_with(line, "SO"))
        set_texture(&map->tex_so, line + 2);
    else if (starts_with(line, "WE"))
        set_texture(&map->tex_we, line + 2);
    else if (starts_with(line, "EA"))
        set_texture(&map->tex_ea, line + 2);
    else if (line[0] == 'F')
        map->floor_color = parse_color(line + 1);
    else if (line[0] == 'C')
        map->ceil_color = parse_color(line + 1);
}

// .cubファイルをパース
void parse_cub_file(char *filename, t_map *map)
{
    int fd;
    char buffer[BUFFER_SIZE + 1];
    size_t bytes_read;
    char *line;
    char *newline;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error opening file\n", 19);
        exit(1);
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        line = buffer;
        while (*line)
        {
            newline = line;
            while (*newline && *newline != '\n')
                newline++;
            if (*newline == '\n')
                *newline++ = '\0';

            parse_line(map, line);
            line = newline;
        }
    }
    close(fd);
}