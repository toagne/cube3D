/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 13:58:25 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_limits(t_table *table, t_minimap *minimap, float scale)
{
	int	map_width_pixels;
	int	map_height_pixels;

	map_width_pixels = T_SIZE * table->columns;
	map_height_pixels = T_SIZE * table->rows;
	if (map_width_pixels < minimap->size / scale)
		minimap->x0 = 0;
	else if (minimap->x0 < 0)
		minimap->x0 = 0;
	else if (minimap->x0 + minimap->view_width > map_width_pixels)
		minimap->x0 = map_width_pixels - minimap->view_width;
	if (map_height_pixels < minimap->size / scale)
		minimap->y0 = 0;
	else if (minimap->y0 < 0)
		minimap->y0 = 0;
	else if (minimap->y0 + minimap->view_height > map_height_pixels)
		minimap->y0 = map_height_pixels - minimap->view_height;
}

void	draw_map(t_table *table, t_minimap minimap, float scale)
{
	int			y;
	int			x;
	int			tile_x;
	int			tile_y;

	y = -1;
	while (++y < minimap.size)
	{
		x = -1;
		while (++x < minimap.size)
		{
			tile_x = minimap.x0 + (x / scale);
			tile_y = minimap.y0 + (y / scale);
			if (tile_x >= 0 && tile_x < (int)(T_SIZE * table->columns) &&
				tile_y >= 0 && tile_y < (int)(T_SIZE * table->rows))
			{
				if (table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '1'
					|| table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '2'
					|| table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '4')
					mlx_put_pixel(table->mlx_minimap, x, y, 0xFFFFFFFF);
				else
					mlx_put_pixel(table->mlx_minimap, x, y, 0x000000FF);
			}
		}
	}
}

void	draw_player_in_map(t_table *t, t_minimap *minimap,
	float scale, int dot_dim)
{
	int		x;
	int		y;
	int		delta_x_scaled;
	int		delta_y_scaled;
	t_line	line;

	minimap->player_x = (t->player_x - minimap->x0) * scale;
	minimap->player_y = (t->player_y - minimap->y0) * scale;
	y = minimap->player_y - dot_dim - 1;
	while (++y <= minimap->player_y + dot_dim)
	{
		x = minimap->player_x - dot_dim - 1;
		while (++x <= minimap->player_x + dot_dim)
			if (y >= 0 && y < minimap->size && x >= 0 && x < minimap->size)
				mlx_put_pixel(t->mlx_minimap, x, y, 0xFFFF00FF);
	}
	delta_x_scaled = t->player_delta_x * scale * t->height / 40;
	delta_y_scaled = t->player_delta_y * scale * t->height / 40;
	line.x0 = minimap->player_x;
	line.y0 = minimap->player_y;
	line.x1 = minimap->player_x + delta_x_scaled;
	line.y1 = minimap->player_y + delta_y_scaled;
	line.color = 0xFFFF00FF;
	draw_line(&line, t, 0, t->mlx_minimap);
}

void	draw_sprites_in_map(t_table *table, t_minimap minimap,
	float scale, int dot_dim)
{
	int	i;
	int	enemy_x_minimap;
	int	enemy_y_minimap;
	int	x;
	int	y;

	i = -1;
	while (++i < N_ENEMIES)
	{
		enemy_x_minimap = (table->enemies[i].x - minimap.x0) * scale;
		enemy_y_minimap = (table->enemies[i].y - minimap.y0) * scale;
		y = enemy_y_minimap - dot_dim - 1;
		while (++y <= enemy_y_minimap + dot_dim)
		{
			x = enemy_x_minimap - dot_dim - 1;
			while (++x <= enemy_x_minimap + dot_dim)
				if (y >= 0 && y < minimap.size && x >= 0 && x < minimap.size)
					mlx_put_pixel(table->mlx_minimap, x, y, 0xFF0000FF);
		}
	}
}

void	draw_minimap(t_table *table)
{
	t_minimap	minimap;
	float		scale;
	int			dot_dim;

	scale = (float)table->width / 5000;
	minimap.size = fmin(table->width / 4, table->height / 4);
	minimap.view_width = minimap.size / scale;
	minimap.view_height = minimap.size / scale;
	minimap.x0 = table->player_x - minimap.view_width / 2;
	minimap.y0 = table->player_y - minimap.view_height / 2;
	check_map_limits(table, &minimap, scale);
	draw_map(table, minimap, scale);
	dot_dim = (float)table->height / 500;
	draw_player_in_map(table, &minimap, scale, dot_dim);
	draw_sprites_in_map(table, minimap, scale, dot_dim);
}
