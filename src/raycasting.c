/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/02 15:36:21 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fix_fisheye(t_table *table, float ray_angle)
{
	int	camera_angle;

	camera_angle = (table->player_angle - ray_angle);
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
	if (table->ray.start_wall < 0)
		table->ray.start_wall = 0;
	table->ray.end_wall = table->ray.wall_h / 2 + table->height / 2;
	if (table->ray.end_wall >= table->height)
		table->ray.end_wall = table->height - 1;
}

void	get_v_lines_for_each_ray(t_table *table, int r, int n_of_rays)
{
	table->ray.x_start = r * (table->width / n_of_rays);
	table->ray.x_end = (r + 1) * (table->width / n_of_rays) - 1;
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

void	draw_raycasting(t_table *table)
{
	float	ray_angle;
	float	angle;
	int		r;

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
