/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 14:03:39 by mpellegr         ###   ########.fr       */
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

void	get_wall_dimensions(t_table *table, float ray_angle,
	int r, int n_of_rays)
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
	table->ray.x_start = r * (table->width / n_of_rays);
	table->ray.x_end = (r + 1) * (table->width / n_of_rays) - 1;
}

void	draw_floor_and_ceiling(t_table *t, int i)
{
	t_line	line;

	line.x0 = i;
	line.y0 = 0;
	line.x1 = i;
	line.y1 = t->ray.start_wall;
	line.color = get_rgba(t->c_color[0], t->c_color[1], t->c_color[2], 255);
	draw_line(&line, t, 1, t->mlx_raycast);
	line.x0 = i;
	line.y0 = t->ray.end_wall;
	line.x1 = i;
	line.y1 = t->height - 1;
	line.color = get_rgba(t->f_color[0], t->f_color[1], t->f_color[2], 255);
	draw_line(&line, t, 1, t->mlx_raycast);
}

void	draw_v_lines(t_table *t)
{
	int	i;
	int	j;
	int	tex_x;
	int	tex_y;

	i = t->ray.x_start;
	while (i <= t->ray.x_end)
	{
		draw_floor_and_ceiling(t, i);
		j = t->ray.start_wall;
		t->ray.ty = t->ray.tx_v_offset * t->ray.tx_v_step;
		while (j <= t->ray.end_wall)
		{
			tex_x = (int)t->ray.tx;
			tex_y = (int)t->ray.ty;
			if (tex_y >= (int)t->ray.texture.height)
				tex_y = t->ray.texture.height - 1;
			if (t->ray.texture.colors[tex_y][tex_x] != t->w_colors[j][i])
				t->w_colors[j][i] = t->ray.texture.colors[tex_y][tex_x];
			t->ray.ty += t->ray.tx_v_step;
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
		select_texture(table, &table->ray.texture);
		get_wall_dimensions(table, ray_angle, r, table->n_of_rays);
		get_coordinates_in_texture(table);
		draw_v_lines(table);
		ray_angle = ray_angle + ((float)60 / table->n_of_rays);
	}
	draw_sprites(table);
	draw_pointer(table);
}
