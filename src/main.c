/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/07 13:55:13 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    read_map(t_table *table, char *infile)
{
    int     i;
    int     bytes;
    int     player_pos;

    table->map_fd = open(infile, O_RDONLY);
    bytes = read(table->map_fd, table->map, sizeof(table->map));
    table->map[bytes] = '\0';
    printf("%s\n", table->map);  
    i = -1;
    table->rows = 1;
    while (table->map[++i] != '\n')
        table->columns = i + 1;
    i = -1;
    while (table->map[++i] != '\0')
        if (table->map[i] == '\n')
            table->rows++;
    printf("%d x %d\n", table->columns, table->rows);
    player_pos = -1;
    while (table->map[++player_pos] != 'N')
        ;
    table->player_y = (player_pos / (table->columns + 1)) + 1;
    table->player_x = player_pos - (table->player_y - 1) * (table->columns + 1) + 1;
}

void draw_map(t_table *table)
{
    double      cell_width;
    double      cell_height;
    int         x;
    int         y;
    int         row;
    int         col;
    int         i;
    int         j;
    uint32_t    color;

    cell_width = (float)1024 / table->columns;
    cell_height = (float)1024 / table->rows;
    row = -1;
    while (++row < table->rows)
    {
        col = -1;
        while (++col < table->columns)
        {
            x = col * cell_width;
            y = row * cell_height;

            if (table->map[row * (table->columns + 1) + col] == '1')
                color = 0xFF0000FF;
            else if (table->map[row * (table->columns + 1) + col] == '0')
                color = 0x00FF00FF;
            //else if (table->map[row * (table->columns + 1) + col] == 'N')
                //color = 0x0000FFFF;
            else
                color = 0x000000FF;
            i = -1;
            while (++i < cell_height)
            {
                j = -1;
                while (++j < cell_width)
                    mlx_put_pixel(table->mlx_image, x + j, y + i, color);
            }
        }
    }
    mlx_image_to_window(table->mlx_start, table->mlx_image, 0, 0);
}

void    draw_player(t_table *table)
{
    double      cell_width;
    double      cell_height;
    int         x;
    int         y;
    int         row;
    int         col;
    int         i;
    int         j;
    uint32_t    color;

    cell_width = (float)1024 / table->columns;
    cell_height = (float)1024 / table->rows;
    color = 0x0000FFFF;
    row = -1;
    while (++row < table->player_y)
    {
        col = -1;
        while (++col < table->player_x)
            ;
    }
    x = (col - 1) * cell_width + (cell_width / 4);
    y = (row - 1) * cell_height + (cell_height / 4);
    i = -1;
    while (++i < cell_height / 2)
    {
        j = -1;
        while (++j < cell_width / 2)
            mlx_put_pixel(table->mlx_image, x + j, y + i, color);
    }
}

int main (int argc, char **argv)
{
    t_table table;

    (void) argc;
    (void) argv;
    if (argc != 2)
    {
        write (2, "wrong input\n", 12);
        exit(EXIT_FAILURE);
    }
    // check that argc 1 is a file that can be opened and read and ends with .cub
    //parse_input();
    init_data(&table);
    table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
    if (!table.mlx_start)
        ;//error
    table.mlx_image = mlx_new_image(table.mlx_start, 1024, 1024);
    if (!table.mlx_image)
		;//error
    read_map(&table, argv[1]);
    draw_map(&table);
    draw_player(&table);
    mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
    mlx_loop(table.mlx_start);
}