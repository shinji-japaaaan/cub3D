/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:36:18 by sishizaw          #+#    #+#             */
/*   Updated: 2025/03/23 18:27:48 by sishizaw         ###   ########.fr       */
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

    // テクスチャパスが空でないかチェック
    if (line[i] == '\0')
        exit(printf("Error: Missing texture path\n"));

    // テクスチャパスをコピー
    char *texture_path = strdup(&line[i]);
    if (!texture_path)
        exit(printf("Error: Memory allocation failed for texture path\n"));

    return texture_path;
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
    if (!filename || strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".cub") != 0)
    {
        printf("Error: Invalid file format (expected .cub file)\n");
        exit(EXIT_FAILURE);
    }

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
    if (!buffer)
    {
        perror("Error: Memory allocation failed for buffer");
        return NULL;
    }

    int bytes_read;
    int i = 0;

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

    if (bytes_read == -1)
    {
        perror("Error reading file");
        free(buffer);
        return NULL;
    }

    if (i == 0) // EOF か空行
    {
        free(buffer);
        return NULL;
    }

    buffer[i] = '\0';
    return buffer;
}

void **custom_realloc(void **ptr, int old_size, int new_size)
{
    void **new_ptr;
    int i;

    // 新しいメモリ領域を確保
    new_ptr = (void **)malloc(sizeof(void *) * new_size);
    if (!new_ptr)
        return NULL;

    // 既存のデータをコピー
    for (i = 0; i < old_size; i++)
        new_ptr[i] = ptr[i];

    // 古いメモリを解放
    free(ptr);

    return new_ptr;
}

char **read_lines(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char **lines = NULL;
    char *line;
    int count = 0;
    int capacity = 20;

    if (fd < 0)
        return NULL;

    // 初期メモリ確保
    lines = (char **)malloc(sizeof(char *) * capacity);
    if (!lines)
    {
        close(fd);
        return NULL;
    }

    // 1行ずつ読み込む
    while ((line = read_line(fd)) != NULL)
    {
        if (count >= capacity - 1)
        {
            int new_capacity = capacity * 2;
            char **new_lines = (char **)custom_realloc(
                (void **)lines, capacity, new_capacity);
            if (!new_lines)
            {
                free(line);
                for (int j = 0; j < count; j++)
                    free(lines[j]);
                free(lines);
                close(fd);
                return NULL;
            }
            lines = new_lines;
            capacity = new_capacity;
        }
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

int validate_cub_format(char **lines)
{
    int has_map = 0;
    int has_config = 0;
    int has_floor = 0;
    int has_ceiling = 0;

    for (int i = 0; lines[i]; i++)
    {
        if (ft_strchr(lines[i], '1')) // マップデータがあるか
            has_map = 1;
        // テクスチャ設定 (完全一致でチェック)
        if (strncmp(lines[i], "NO ", 3) == 0 || strncmp(lines[i], "SO ", 3) == 0 ||
            strncmp(lines[i], "WE ", 3) == 0 || strncmp(lines[i], "EA ", 3) == 0)
            has_config = 1;

        // 床の色 (Floor)
        if (strncmp(lines[i], "F ", 2) == 0)
            has_floor = 1;

        // 天井の色 (Ceiling)
        if (strncmp(lines[i], "C ", 2) == 0)
            has_ceiling = 1;
    }
    if (!has_map || !has_config || !has_floor || !has_ceiling)
        return 0;
    return 1;
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
        exit(EXIT_FAILURE);
    }
    // ファイルフォーマットが正しいかチェック
    if (!validate_cub_format(lines))
    {
        // フォーマットエラーの場合、メモリ解放して終了
        free_lines(lines);
        printf("Error: Invalid .cub file format\n");
        exit(EXIT_FAILURE);
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
