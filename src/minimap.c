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

void	convert_rays_for_minimap(t_table *table, float angle, float ray_angle)
{
	int minimap_size = fmin(table->width / 4, table->height / 4);
	// printf("minimap size = %d\n", minimap_size);
	int vpx0 = (table->player_x - (minimap_size / 2));
	int vpy0 = (table->player_y - (minimap_size / 2));
	int vpx1 = vpx0 + minimap_size;
	int vpy1 = vpy0 + minimap_size;
	// printf("fx = %f	fy = %f\n", fx, fy);
	// printf("vpx0 = %d	vpx1 = %d\n", vpx0, vpx1);
	// printf("vpy0 = %d	vpy1 = %d\n", vpy0, vpy1);
	int rx1 = table->ray.f_x;
	int ry1 = table->ray.f_y;
	if (vpx0 > table->ray.f_x && (vpx0 - table->ray.f_x) > (vpy0 - table->ray.f_y) && (vpx0 - table->ray.f_x) > (table->ray.f_y - vpy1))
	{
		rx1 = vpx0;
		ry1 = -(table->player_x - rx1) * tan(angle) + table->player_y;
	}
	if (vpx1 < table->ray.f_x && (table->ray.f_x - vpx1) > (table->ray.f_y - vpy1) && (table->ray.f_x - vpx1) > (vpy0 - table->ray.f_y))
	{
		rx1 = vpx1;
		if (ray_angle == 0 || ray_angle == 360)
			ry1 = table->player_y;
		else
			ry1 = -(table->player_x - rx1) * tan(angle) + table->player_y;
	}
	if (vpy0 > table->ray.f_y && (vpy0 - table->ray.f_y) > (vpx0 - table->ray.f_x) && (vpy0 - table->ray.f_y) > (table->ray.f_x - vpx1))
	{
		ry1 = vpy0;
		if (ray_angle == 270)
			rx1 = table->player_x;
		else
			rx1 = -(table->player_y - ry1) / tan(angle) + table->player_x;
	}
	if (vpy1 < table->ray.f_y && (table->ray.f_y - vpy1) > (table->ray.f_x - vpx1) && (table->ray.f_y - vpy1) > (vpx0 - table->ray.f_x))
	{
		ry1 = vpy1;
		rx1 = -(table->player_y - ry1) / tan(angle) + table->player_x;
	}
	rx1 -= vpx0;
	ry1 -= vpy0;
	if (rx1 == minimap_size)
		rx1 -= 1;
	if (ry1 == minimap_size)
		ry1 -= 1;	
	// printf("player x%f	player y%f\n", table->player_x, table->player_y);
	// printf("rx1 = %d	ry1 = %d\n", rx1, ry1);
	// printf("angle = %f\n", ray_angle);
	
	// draw_line(table->mlx_2D, table->player_x - vpx0, table->player_y - vpy0, rx1, ry1, 0xFFFF00FF, table, 0);
}

void draw_filled_circle(void *mlx_2D, int cx, int cy, int radius, uint32_t color)
{
    int x_start = cx - radius;
    int x_end = cx + radius;
    int y_start = cy - radius;
    int y_end = cy + radius;

    for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
            // Check if the point is within the circle
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius) {
                mlx_put_pixel(mlx_2D, x, y, color);
            }
        }
    }
}

void draw_real_minimap(t_table *table, float scale)
{
	int minimap_size = fmin(table->width / 4, table->height / 4); // Fixed minimap size
	int view_width = minimap_size / scale; // Viewport width in map units
	int view_height = minimap_size / scale; // Viewport height in map units
	int x0 = table->player_x - view_width / 2; // Top-left corner of the scaled view
	int y0 = table->player_y - view_height / 2;

	// Clamp the scaled viewport to the map boundaries
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x0 + view_width > (int)(T_SIZE * table->columns))
		x0 = T_SIZE * table->columns - view_width;
	if (y0 + view_height > (int)(T_SIZE * table->rows))
		y0 = T_SIZE * table->rows - view_height;

	// Draw the map content scaled into the fixed minimap size
	int	i = 0;
	int j;
	while (i < minimap_size)
	{
		j = 0;
		while (j < minimap_size)
		{
			// Map the minimap pixel to a map tile based on scale
			int tile_x = x0 + (j / scale);
			int tile_y = y0 + (i / scale);

			// Ensure the tile coordinates are within map bounds
			if (tile_x >= 0 && tile_x < (int)(T_SIZE * table->columns) &&
				tile_y >= 0 && tile_y < (int)(T_SIZE * table->rows)) 
			{
				uint32_t color;
				if (table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '1' || table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '2' || table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '4')
					color = 0xFFFFFFFF;
				else
					color = 0x000000FF;
				mlx_put_pixel(table->mlx_2D, j, i, color);
			}
			j++;
		}
		i++;
	}

	// Calculate the player's scaled position on the minimap
	int player_x_minimap = (table->player_x - x0) * scale;
	int player_y_minimap = (table->player_y - y0) * scale;

	// Draw player marker in the scaled minimap
	i = player_y_minimap - 3;
	while (++i <= player_y_minimap + 2)
	{
		j = player_x_minimap - 3;
		while (++j <= player_x_minimap + 2)
			if (i >= 0 && i < minimap_size && j >= 0 && j < minimap_size)
				mlx_put_pixel(table->mlx_2D, j, i, 0xFFFF00FF);
	}
	// Calculate scaled deltas for direction vector
	int delta_x_scaled = table->player_delta_x * scale * 30; // Adjust the multiplier for line length
	int delta_y_scaled = table->player_delta_y * scale * 30;

	// Line endpoint based on scaled deltas
	int line_end_x = player_x_minimap + delta_x_scaled;
	int line_end_y = player_y_minimap + delta_y_scaled;

	// Draw the directional line
	draw_line(table->mlx_2D, player_x_minimap, player_y_minimap, line_end_x, line_end_y, 0xFFFF00FF, table, 0);

	i = -1;
	while (++i < N_ENEMIES)
	{
		// Calculate enemy position in the minimap
		int enemy_x_minimap = (table->enemies[i].x - x0) * scale;
		int enemy_y_minimap = (table->enemies[i].y - y0) * scale;

		// Check if the enemy is within the minimap bounds
		int y = enemy_y_minimap - 3;
		while (++y <= enemy_y_minimap + 2)
		{
			int x = enemy_x_minimap - 3;
			while (++x <= enemy_x_minimap + 2)
				if (y >= 0 && y < minimap_size && x >= 0 && x < minimap_size)
					mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
		}
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
	if (table->map[row][col] == '1' || table->map[row][col] == '2' || table->map[row][col] == '4')
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
/* 	size_t	row;
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
	draw_player(table); */
	draw_real_minimap(table, 0.5);
}
