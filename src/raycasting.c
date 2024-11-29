/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/29 13:05:33 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int find_increment(int i0, int i1)
{
	int i;

	if (i0 < i1)
		i = 1;
	else
		i = -1;
	return (i);
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	sx = find_increment(x0, x1);
	sy = find_increment(y0, y1);
	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;// Stop if we’ve reached the end point
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

void	get_final_values(t_table *table, char side, float side_tile_x, float side_tile_y)
{
	int		p_x;
	int		p_y;

	p_x = table->player_x;
	p_y = table->player_y;
	if (side == 'v')
	{
		table->ray.v_v = sqrt((p_x - side_tile_x) * (p_x - side_tile_x) + (p_y - side_tile_y) * (p_y - side_tile_y));
		table->ray.v_x = side_tile_x;
		table->ray.v_y = side_tile_y;
	}
	else if (side == 'h')
	{
		table->ray.h_v = sqrt((p_x - side_tile_x) * (p_x - side_tile_x) + (p_y - side_tile_y) * (p_y - side_tile_y));
		table->ray.h_x = side_tile_x;
		table->ray.h_y = side_tile_y;
	}
}

void	check_if_wall(t_table *table, float step_x, float step_y, float side_tile_x, float side_tile_y, char side)
{
	int	map_x;
	int map_y;

	while (side_tile_x > 0 && side_tile_y > 0 && side_tile_x < T_SIZE * table->columns && side_tile_y < T_SIZE * table->rows)
	{
		map_x = side_tile_x / T_SIZE;
		map_y = side_tile_y / T_SIZE;

		if (table->map[map_y][map_x] == '1')
			break;
		else
		{
			side_tile_x+=step_x;
			side_tile_y+=step_y;
		}
	}
	get_final_values(table, side, side_tile_x, side_tile_y);
}

void	check_horizontal_lines(t_table *table, float angle)
{
	float	step_x;
	float	step_y;
	float	h_vector;
	float	h_side_tile_x;
	float	h_side_tile_y;

	h_vector = 10000;
	if (angle > 0 && angle < PI)
	{
		h_side_tile_y = (int)(table->player_y / T_SIZE) * T_SIZE + T_SIZE;
		h_side_tile_x = -(table->player_y - h_side_tile_y) / tan(angle) + table->player_x;
		step_y = T_SIZE;
		step_x = T_SIZE / tan(angle);
	}
	else
	{
		h_side_tile_y = (int)(table->player_y / T_SIZE) * T_SIZE - 0.0001;
		h_side_tile_x = -(table->player_y - h_side_tile_y) / tan(angle) + table->player_x;
		step_y = -T_SIZE;
		step_x = -(T_SIZE / tan(angle));
	}
	check_if_wall(table, step_x, step_y, h_side_tile_x, h_side_tile_y, 'h');
}

void	check_vertical_lines(t_table *table, float angle)
{
	float	step_x;
	float	step_y;
	float	v_vector;
	float	v_side_tile_x;
	float	v_side_tile_y;

	v_vector = 10000;
	if (angle > 3 *PI / 2 || angle < PI / 2)
	{
		v_side_tile_x = (int)(table->player_x / T_SIZE) * T_SIZE + T_SIZE;
		v_side_tile_y = -(table->player_x - v_side_tile_x) * tan(angle) + table->player_y;
		step_x = T_SIZE;
		step_y = T_SIZE * tan(angle);
	}
	else
	{
		v_side_tile_x = (int)(table->player_x / T_SIZE) * T_SIZE - 0.0001;
		v_side_tile_y = -(table->player_x - v_side_tile_x) * tan(angle) + table->player_y;
		step_x = -T_SIZE;
		step_y = -T_SIZE * tan(angle);
	}
	check_if_wall(table, step_x, step_y, v_side_tile_x, v_side_tile_y, 'v');
}

void	chose_shortest_ray(t_table *table)
{
	if (table->ray.v_v > table->ray.h_v)
	{
		table->ray.f_v = table->ray.h_v;
		table->ray.f_x = table->ray.h_x;
		table->ray.f_y = table->ray.h_y;
	}
	else
	{
		table->ray.f_v = table->ray.v_v;
		table->ray.f_x = table->ray.v_x;
		table->ray.f_y = table->ray.v_y;
	}
}

void	check_side_of_wall(t_table *table, t_texture *tx, float dx, float dy)
{
	if (dy > dx && dy > (T_SIZE - dx))
	{
		tx->height = table->no_texture.height;
		tx->width = table->no_texture.width;
		tx->colors = table->no_texture.colors;
	}
	else if (dy < dx && dy < (T_SIZE - dx))
	{
		tx->height = table->so_texture.height;
		tx->width = table->so_texture.width;
		tx->colors = table->so_texture.colors;
	}
	else if (dx <= dy && dx <= (T_SIZE - dy))
	{
		tx->height = table->ws_texture.height;
		tx->width = table->ws_texture.width;
		tx->colors = table->ws_texture.colors;
	}
	else
	{
		tx->height = table->es_texture.height;
		tx->width = table->es_texture.width;
		tx->colors = table->es_texture.colors;
	}
}

void	select_texture(t_table *table, t_texture *tx)
{
	int			tile_x;
	int			tile_y;
	float 		dx;
	float 		dy;

	tile_x = (int)(table->ray.f_x / T_SIZE) * T_SIZE;
	tile_y = (int)(table->ray.f_y / T_SIZE) * T_SIZE;
	dx = table->ray.f_x - tile_x;
	dy = table->ray.f_y - tile_y;
	check_side_of_wall(table, tx, dx, dy);
}

void	fix_fisheye(t_table *table, float ray_angle)
{
	int	camera_angle;

	camera_angle=(table->player_angle - ray_angle);
	if (camera_angle > 359)
		camera_angle -= 360;
	if (camera_angle < 0)
		camera_angle += 360;
	table->ray.f_v = table->ray.f_v * cos(deg_to_rad(camera_angle));
}

void	get_wall_dimensions(t_table *table, float ray_angle)
{
	fix_fisheye(table, ray_angle);
	table->ray.wall_h = T_SIZE * table->height / table->ray.f_v;
	table->ray.tx_v_step = (float)table->ray.texture.height / table->ray.wall_h;
	table->ray.tx_v_offset = 0;
	if (table->ray.wall_h > table->height)
	{
		table->ray.tx_v_offset = (table->ray.wall_h - table->height) / 2;
		table->ray.wall_h = table->height;
	}
	table->ray.start_wall = table->height / 2 - table->ray.wall_h / 2;
	if(table->ray.start_wall < 0)
		table->ray.start_wall = 0;
	table->ray.end_wall = table->ray.wall_h / 2 + table->height / 2;
	if(table->ray.end_wall >= table->height)
		table->ray.end_wall = table->height - 1;
}

void	get_v_lines_for_each_ray(t_table *table, int r, int n_of_rays)
{
	table->ray.x_start = r * (table->width / n_of_rays);
	table->ray.x_end = (r + 1) * (table->width / n_of_rays) - 1;
}

void	get_coordinates_in_texture(t_table *table)
{
	table->ray.ty = table->ray.tx_v_offset * table->ray.tx_v_step;
	if (table->ray.v_v > table->ray.h_v)
	{
		table->ray.tx = ((int)table->ray.f_x % T_SIZE) * table->ray.texture.width / T_SIZE;
		if (table->player_angle < 180)
		{
			if (table->ray.tx == 0)
				table->ray.tx = table->ray.texture.width;
			table->ray.tx = table->ray.texture.width - table->ray.tx;
		}
	}
	else
	{
		table->ray.tx = ((int)table->ray.f_y % T_SIZE) * table->ray.texture.width / T_SIZE;
		if (table->player_angle > 90 && table->player_angle < 270)
		{
			if (table->ray.tx == 0)
				table->ray.tx = table->ray.texture.width;
			table->ray.tx = table->ray.texture.width - table->ray.tx;
		}
	}
}

void	draw_v_lines(t_table *table)
{
	int	i;
	int	j;
	int	tex_x;
	int	tex_y;

	i = table->ray.x_start;
	while (i <= table->ray.x_end)
	{
		draw_line(table->mlx_3D, i, 0, i, table->ray.start_wall, 0xADD8E6FF);
		draw_line(table->mlx_3D, i, table->ray.end_wall, i, table->height - 1, 0x8B4513FF);
		j = table->ray.start_wall;
		table->ray.ty = table->ray.tx_v_offset * table->ray.tx_v_step;
		while (j <= table->ray.end_wall)
		{
			tex_x = (int)table->ray.tx;
			tex_y = (int)table->ray.ty;
			if (tex_y >= (int)table->ray.texture.height)
				tex_y = table->ray.texture.height - 1;
			mlx_put_pixel(table->mlx_3D, i, j, table->ray.texture.colors[tex_y][tex_x]);
			table->ray.ty += table->ray.tx_v_step;
			j++;
		}
		i++;
	}
}

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
	
	//draw_line(table->mlx_2D, table->player_x - vpx0, table->player_y - vpy0, rx1, ry1, 0xFFFF00FF);
}

void	draw_raycasting(t_table *table)
{
	float ray_angle;
	float angle;
	int r;

	ray_angle = table->player_angle - 30;
	r = -1;
	while (++r < table->n_of_rays)
	{
		if (ray_angle > 359)
			ray_angle -= 360;
		if (ray_angle < 0)
			ray_angle += 360;
		angle = deg_to_rad(ray_angle);
		check_vertical_lines(table, angle);
		check_horizontal_lines(table, angle);
		chose_shortest_ray(table);
		// following line not needed
		draw_line(table->mlx_2D, table->player_x / 2, table->player_y / 2, table->ray.f_x / 2, table->ray.f_y / 2, 0xFFFF00FF);
		convert_rays_for_minimap(table, angle, ray_angle);
		select_texture(table, &table->ray.texture);
		get_wall_dimensions(table, ray_angle);
		get_v_lines_for_each_ray(table, r, table->n_of_rays);
		get_coordinates_in_texture(table);
		draw_v_lines(table);
		ray_angle = ray_angle + ((float)60 / table->n_of_rays);
	}
	draw_sprites(table);
}
