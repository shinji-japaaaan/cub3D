/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/23 11:04:21 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int parse_color(char *line)
{
    int i = 1; // "F" または "C" の次の文字から開始
    int r, g, b;

    // 空白をスキップ
    while (line[i] == ' ')
        i++;

    // 赤色値の取得
    r = atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i++] != ',')
        exit(printf("Error: Invalid color format\n"));

    // 緑色値の取得
    g = atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i++] != ',')
        exit(printf("Error: Invalid color format\n"));

    // 青色値の取得
    b = atoi(&line[i]);

    // RGB値の範囲チェック
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        exit(printf("Error: RGB values out of range\n"));

    // RGBを16進数に変換して返す
    return (r << 16 | g << 8 | b);
}

char *parse_texture(char *line)
{
    int i = 2; // "NO", "SO", "WE", "EA" の後ろからスタート

    // 空白をスキップ
    while (line[i] == ' ')
        i++;

    // テクスチャパスをコピー
    return strdup(&line[i]);
}

char **parse_map(char **lines, int start, int height)
{
    char **map;
    int i;

    // メモリ確保
    map = (char **)malloc(sizeof(char *) * (height + 1));
    if (!map)
        exit(printf("Error: Memory allocation failed\n"));

    i = 0;
    // マップをコピー
    while (i < height)
    {
        map[i] = strdup(lines[start + i]);
        if (!map[i])
            exit(printf("Error: Memory allocation failed\n"));
        i++;
    }
    map[i] = NULL; // NULL 終端

    return map;
}


int open_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fd;
}


char *read_line(int fd)
{
    char *buffer = malloc(BUFFER_SIZE);
    int bytes_read;
    int i = 0;

    if (!buffer)
        return NULL;

    while ((bytes_read = read(fd, &buffer[i], 1)) > 0)
    {
        if (buffer[i] == '\n' || buffer[i] == '\0')
        {
            buffer[i] = '\0';
            return buffer;
        }
        i++;
        if (i >= BUFFER_SIZE - 1)
            break;
    }
    free(buffer);
    return NULL;
}


char **read_lines(const char *filename)
{
    int fd = open_file(filename);
    char **lines = NULL;
    char *line;
    int count = 0;

    lines = malloc(sizeof(char *) * (BUFFER_SIZE));
    if (!lines)
        return NULL;

    while ((line = read_line(fd)) != NULL)
    {
        lines[count++] = line;
    }
    lines[count] = NULL; // NULL 終端

    close(fd);
    return lines;
}


void free_lines(char **lines)
{
    int i = 0;
    while (lines[i])
        free(lines[i++]);
    free(lines);
}


void parse_cub_file(const char *filename, t_map *map)
{
    char **lines;
    int i = 0;
    int map_start = 0;
    int map_height = 0;

    // linesに全行を読み込む
    lines = read_lines(filename);
    if (!lines)
    {
        printf("Error: Failed to read file\n");
        return;
    }

    // 各行を解析してマップ情報を格納
    while (lines[i])
    {
        if (strncmp(lines[i], "NO ", 3) == 0)
            map->tex_no = parse_texture(lines[i]);
        else if (strncmp(lines[i], "SO ", 3) == 0)
            map->tex_so = parse_texture(lines[i]);
        else if (strncmp(lines[i], "WE ", 3) == 0)
            map->tex_we = parse_texture(lines[i]);
        else if (strncmp(lines[i], "EA ", 3) == 0)
            map->tex_ea = parse_texture(lines[i]);
        else if (lines[i][0] == 'F')
            map->floor_color = parse_color(lines[i]);
        else if (lines[i][0] == 'C')
            map->ceil_color = parse_color(lines[i]);
        else if (lines[i][0] == '1' || lines[i][0] == '0' || 
                 lines[i][0] == 'N' || lines[i][0] == 'S' || 
                 lines[i][0] == 'E' || lines[i][0] == 'W')
        {
            if (map_start == 0)
                map_start = i;
            map_height++;
        }
        i++;
    }

    // マップ情報を解析して格納
    map->grid = parse_map(lines, map_start, map_height);
    map->height = map_height;
    map->width = strlen(map->grid[0]);

    // 使用したメモリの解放
    free_lines(lines);
}
