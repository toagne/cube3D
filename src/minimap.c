/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/20 16:14:22 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	draw_background_not_needed(t_table *table, int m_tile)
{
	int	x;
	int	y;

	//h = T_SIZE * table->rows;
	//w = T_SIZE * table->columns;
	y = -1;
	while (++y < m_tile)
	{
		x = -1;
		while (++x < m_tile)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
	}
}

void	draw_tile(t_table *table, int col, int row, int x0, int y0)
{
	int			x;
	int			y;
	int			i;
	int			j;
	uint32_t	color;

	printf("\ncol = %d	row = %d\n", col, row);
	x = fmax(col * T_SIZE, x0);
	y = fmax(row * T_SIZE, y0);
	printf("top let corner of view = %d	%d\n", x, y);
	if (table->map[row][col] == '1')
		color = 0xFFFFFFFF;
	else
		color = 0x000000FF;
	i = -1;
	while (++i < T_SIZE - (y0 - y) - 1)
	{
		j = -1;
		while (++j < T_SIZE - (x0 - x) - 1)
			mlx_put_pixel(table->mlx_2D, x + j, y + i, color);
	}
}

void	draw_player(t_table *table, int x0, int y0)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = (table->player_y - y0) - 1;
	while (y++ < (table->player_y - y0) + 1)
	{
		x = (table->player_x - x0) - 1;
		while (x++ < (table->player_x - x0) + 1)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFFFF00FF);
	}
}

void	draw_minimap(t_table *table)
{
	int	row;
	int	col;
	int		minimap_t;

	minimap_t = fmin(table->width / 5, table->height / 5);
	int x0 = table->player_x - (minimap_t / 2);
	int y0 = table->player_y - (minimap_t / 2);
	int x1 = x0 + minimap_t;
	int y1 = y0 + minimap_t;
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x1 > table->player_x + minimap_t)
		x1 = minimap_t;
	if (y1 > table->player_y + minimap_t)
		y1 = minimap_t;
	int start_col = x0 / T_SIZE;
	int end_col = x1 / T_SIZE;
	int start_row = y0 / T_SIZE;
	int end_row = y1 / T_SIZE;
	printf("minimap_t = %d\n", minimap_t);
	printf("player x = %f	player y = %f\n", table->player_x, table->player_y);
	printf("x0 = %d	x1 = %d\n", x0, x1);
	printf("y0 = %d	y1 = %d\n", y0, y1);
	printf("start_col = %d	end_col = %d\n", start_col, end_col);
	printf("start_row = %d	end_row = %d\n", start_row, end_row);
	//draw_background_not_needed(table, minimap_t);
	printf("\n-------------------------\n");
	row = start_row;
	while (row < end_row)
	{
		col = start_col;
		while (col < end_col)
		{
			draw_tile(table, col, row, x0, y0);
			++col;
		}
		++row;
	}
	draw_player(table, x0, y0);
}*/



void	draw_real_minimap(t_table *table)
{
	int	minimap_size;
	int	x0;
	int	y0;
	int x1;
	int y1;

	minimap_size = fmin(table->width / 5, table->height / 5);
	printf("minimap_size = %d\n", minimap_size);
	printf("player x = %f	player y = %f\n", table->player_x, table->player_y);
	x0 = (table->player_x - (minimap_size / 2));
	y0 = (table->player_y - (minimap_size / 2));
	x1 = x0 + minimap_size;
	y1 = y0 + minimap_size;
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	printf("x0 = %d	y0 = %d\n", x0, y0);
	printf("x1 = %d	y1 = %d\n", x1, y1);
}

void	draw_background_not_needed(t_table *table)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < T_SIZE * table->rows)
	{
		x = -1 + 1000;
		while (++x < T_SIZE * table->columns + 1000)
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

	x = col * T_SIZE;
	y = row * T_SIZE;
	if (table->map[row][col] == '1')
		color = 0xFFFFFFFF;
	else
		color = 0x000000FF;
	i = -1;
	while (++i < T_SIZE - 1)
	{
		j = -1 + 1000;
		while (++j < T_SIZE - 1 + 1000)
			mlx_put_pixel(table->mlx_2D, x + j, y + i, color);
	}
}

void	draw_player(t_table *table)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = table->player_y - 5;
	while (y++ < table->player_y + 5)
	{
		x = table->player_x - 5 + 1000;
		while (x++ < table->player_x + 5 + 1000)
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
	draw_real_minimap(table);
}
