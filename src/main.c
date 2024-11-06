/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/06 15:22:44 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    read_map(t_table *table, char *infile)
{
    int     i;
    int     bytes;

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

    cell_width = /*(float)*/table->width / table->columns;
    cell_height = /*(float)*/table->height / table->rows;
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
            else
                color = 0x000000FF;
            i = -1;
            while (++i < cell_height - 1)
            {
                j = -1;
                while (++j < cell_width - 1)
                    mlx_put_pixel(table->mlx_image, x + j, y + i, color);
            }
        }
    }

    mlx_image_to_window(table->mlx_start, table->mlx_image, 0, 0);
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
    table.mlx_image = mlx_new_image(table.mlx_start, table.width, table.height);
    if (!table.mlx_image)
		;//error
    read_map(&table, argv[1]);
    draw_map(&table);
    mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
    mlx_loop(table.mlx_start);
}