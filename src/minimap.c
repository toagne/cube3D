/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 12:53:25 by mpellegr         ###   ########.fr       */
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
	uint32_t	color;

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
					color = 0xFFFFFFFF;
				else
					color = 0x000000FF;
				mlx_put_pixel(table->mlx_minimap, x, y, color);
			}
		}
	}
}

void	draw_player_in_map(t_table *table, t_minimap *minimap,
	float scale, int dot_dim)
{
	int	x;
	int	y;
	int	delta_x_scaled;
	int	delta_y_scaled;

	minimap->player_x = (table->player_x - minimap->x0) * scale;
	minimap->player_y = (table->player_y - minimap->y0) * scale;
	y = minimap->player_y - dot_dim - 1;
	while (++y <= minimap->player_y + dot_dim)
	{
		x = minimap->player_x - dot_dim - 1;
		while (++x <= minimap->player_x + dot_dim)
			if (y >= 0 && y < minimap->size && x >= 0 && x < minimap->size)
				mlx_put_pixel(table->mlx_minimap, x, y, 0xFFFF00FF);
	}
	delta_x_scaled = table->player_delta_x * scale * table->height / 40;
	delta_y_scaled = table->player_delta_y * scale * table->height / 40;
	draw_line(table->mlx_minimap, minimap->player_x, minimap->player_y,
		minimap->player_x + delta_x_scaled,
		minimap->player_y + delta_y_scaled, 0xFFFF00FF, table, 0);
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

/*void	draw_background_not_needed(t_table *table)
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
	float	scale = (float)table->width / 5000;
	draw_real_minimap(table, scale);
}*/
/*void	convert_rays_for_minimap(t_table *table, float angle, float ray_angle)
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
}*/
