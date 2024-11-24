///* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/21 14:26:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_real_minimap(t_table *table)
{
	int	minimap_size;
	int	x0;
	int	y0;
	int x1;
	int y1;

	minimap_size = fmin(table->width / 4, table->height / 4);
	// printf("minimap_size = %d\n", minimap_size);
	// printf("player x = %f	player y = %f\n", table->player_x, table->player_y);
	x0 = (table->player_x - (minimap_size / 2));
	y0 = (table->player_y - (minimap_size / 2));
	x1 = x0 + minimap_size;
	y1 = y0 + minimap_size;
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x1 > (int)(T_SIZE * table->columns - 1))
		x1 = T_SIZE * table->columns - 1;
	if (y1 > (int)(T_SIZE * table->columns - 1))
		y1 = T_SIZE * table->columns - 1;
	
	// printf("x0 = %d	y0 = %d\n", x0, y0);
	// printf("x1 = %d	y1 = %d\n", x1, y1);
	
	// size_t y, x;
	// y = -1;
	// while (++y < T_SIZE * table->rows)
	// {
	// 	x = -1 + 1000;
	// 	while (++x < T_SIZE * table->columns + 1000)
	// 	{
	// 		if ((int)x == x0 + 1000 || (int)x == x1 + 1000 || (int)y == y0 || (int)y == y1)
	// 			mlx_put_pixel(table->mlx_2D, x, y, 0x00FF00FF);
	// 	}
	// }
	
	uint32_t	minimap[minimap_size][minimap_size];
	int i, j;
	i = -1;
	while (++i < minimap_size)
	{
		j = -1;
		int tile_y = y0 / T_SIZE;
		x0 = (table->player_x - (minimap_size / 2));
		while (++j < minimap_size)
		{
			int tile_x = x0 / T_SIZE;
			if (table->map[tile_y][tile_x] == '1')
				minimap[i][j] = 0xFFFFFFFF;
			else
				minimap[i][j] = 0x000000FF;
			mlx_put_pixel(table->mlx_2D, j, i, minimap[i][j]);
			x0++;
			if (x0 > (int)(T_SIZE * table->columns - 1))
				x0 = T_SIZE * table->columns - 1;
		}
		y0++;
		if (y0 > (int)(T_SIZE * table->rows - 1))
			y0 = T_SIZE * table->rows - 1;
	}
	x0 = (table->player_x - (minimap_size / 2));
	y0 = (table->player_y - (minimap_size / 2));
	i = table->player_y - y0 - 5;
	while (i++ < table->player_y - y0 + 5)
	{
		j = table->player_x - x0 - 5;
		while (j++ < table->player_x - x0 + 5)
			mlx_put_pixel(table->mlx_2D, j, i, 0xFFFF00FF);
	}
}

void	draw_background_not_needed(t_table *table)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < T_SIZE * table->rows / 4)
	{
		x = -1;
		while (++x < T_SIZE * table->columns / 4)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
	}
}

void	draw_tile(t_table *table, int col, int row)
{
	int			x;
	int			y;
	int			i;
	int			j;
	uint32_t	color;

	x = col * T_SIZE / 4;
	y = row * T_SIZE / 4;
	if (table->map[row][col] == '1')
		color = 0xFFFFFFFF;
	else
		color = 0x000000FF;
	i = -1;
	while (++i < T_SIZE / 4 - 1)
	{
		j = -1;
		while (++j < T_SIZE / 4 - 1)
			mlx_put_pixel(table->mlx_2D, x + j, y + i, color);
	}
}

void	draw_player(t_table *table)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = table->player_y / 4 - 5;
	while (y++ < table->player_y / 4 + 5)
	{
		x = table->player_x / 4 - 5;
		while (x++ < table->player_x / 4 + 5)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFFFF00FF);
	}
}

void	draw_minimap(t_table *table)
{
	size_t	row;
	size_t	col;

	draw_background_not_needed(table);
	row = 0;
	while (row < table->rows)
	 {
	 	col = 0;
	 	while (col < table->columns)
	 	{
	 		draw_tile(table, col, row);
	 		++col;
		}
		++row;
	}
	draw_player(table);
	//draw_real_minimap(table);
}
