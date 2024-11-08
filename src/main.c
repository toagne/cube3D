/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/08 09:52:47 by mpellegr         ###   ########.fr       */
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
    table->player_row = (player_pos / (table->columns + 1)) + 1;
    table->player_col = player_pos - (table->player_row - 1) * (table->columns + 1) + 1;
    printf("%d x %d\n", table->player_col, table->player_row);
    table->player_x = (float)table->player_col * 500 / table->columns - (500 / table->columns) / 2;
    table->player_y = (float)table->player_row * 500 / table->rows - (500 / table->rows) / 2;
    printf("%f x %f\n", table->player_x, table->player_y);
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

    cell_width = (float)500 / table->columns;
    cell_height = (float)500 / table->rows;
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
                color = 0xFFFFFFFF;
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

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    err = dx - dy;
    if (x0 < x1)
        sx = 1;
    else
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;   
    while (1)
    {
        mlx_put_pixel(img, x0, y0, color);  // Draw the pixel at (x0, y0)
        if (x0 == x1 && y0 == y1)
            break;    // Stop if we’ve reached the end point
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void    draw_player(t_table *table)
{
   int  x;
   int  y;

    y = table->player_y - 10;
    while (y++ < table->player_y + 10)
    {
        x = table->player_x - 10;
        while (x++ < table->player_x + 10)
            mlx_put_pixel(table->mlx_image, x, y, 0x000000FF);
    }
    draw_line(table->mlx_image, table->player_x, table->player_y, table->player_x+table->player_delta_x, table->player_y+table->player_delta_y, 0x000000FF);
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
    table.mlx_image = mlx_new_image(table.mlx_start, 500, 500);
    if (!table.mlx_image)
		;//error
    read_map(&table, argv[1]);
    draw_map(&table);
    draw_player(&table);
    mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
    mlx_loop(table.mlx_start);
}