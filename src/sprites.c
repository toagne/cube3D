/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:56:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/04 13:42:39 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_table *table, t_enemy sp, int x)
{
	int	tex_x;
	int	tex_y;
	int	y;

	tex_x = ((x - sp.x_start) * table->sprite_tx.width)
		/ sp.screen_size + sp.tx_start_x;
	y = sp.y_start - 1;
	while (++y < sp.y_end)
	{
		tex_y = (y - sp.y_start) * (table->sprite_tx.height - 1)
			/ sp.screen_size;
		if (table->sprite_tx.colors[tex_y][tex_x] != 0x00000000)
		{
			if (table->sprite_tx.colors[tex_y][tex_x] != table->w_colors[y][x])
				table->w_colors[y][x] = table->sprite_tx.colors[tex_y][tex_x];
			//mlx_put_pixel(table->mlx_3D, x, y,
			//	table->sprite_tx.colors[tex_y][tex_x]);
		}
	}
}

void	select_texture_part_size_and_draw(t_table *table, t_enemy sp)
{
	int		x;
	float	column_angle;
	float	angle;

	x = sp.x_start - 1;
	while (++x < sp.x_end)
	{
		column_angle = table->player_angle + (x - table->width / 2)
			* (60.0 / table->width);
		if (column_angle < 0)
			column_angle += 360;
		if (column_angle >= 360)
			column_angle -= 360;
		angle = deg_to_rad(column_angle);
		check_vertical_lines(table, angle);
		check_horizontal_lines(table, angle);
		chose_shortest_ray(table);
		if (sp.dist > table->ray.f_v)
			continue ;
		draw_sprite(table, sp, x);
	}
}

void	render_sprite(t_table *table, int i)
{
	float	angle_diff;

	draw_dot(table, table->enemies[i].x / 4, table->enemies[i].y / 4, 2);
	table->enemies[i].angle = atan2(table->enemies[i].dy,
			table->enemies[i].dx) * 180 / PI;
	if (table->enemies[i].angle < 0)
		table->enemies[i].angle += 360;
	angle_diff = table->enemies[i].angle - table->player_angle;
	if (angle_diff > 180)
		angle_diff -= 360;
	if (angle_diff < -180)
		angle_diff += 360;
	if (check_sprite_is_visible(table, table->enemies[i]))
	{
		convert_sprite_sizes(table, angle_diff, &table->enemies[i]);
		select_texture_part_size_and_draw(table, table->enemies[i]);
	}
}

void	order_sprites(t_table *table, t_enemy *sp)
{
	int		i;
	int		j;
	t_enemy	temp;

	i = -1;
	while (++i < N_ENEMIES)
	{
		sp[i].dx = sp[i].x - table->player_x;
		sp[i].dy = sp[i].y - table->player_y;
		sp[i].dist = sqrt((sp[i].dx * sp[i].dx) + (sp[i].dy * sp[i].dy));
		if (sp[i].dist < 30)
		{
			init_dynamic_data(table);
			display_gameover(table);
		}
	}
	i = -1;
	while (++i < N_ENEMIES - 1)
	{
		j = -1;
		while (++j < N_ENEMIES - i - 1)
		{
			if (sp[j].dist < sp[j + 1].dist)
			{
				temp = sp[j];
				sp[j] = sp[j + 1];
				sp[j + 1] = temp;
			}
		}
	}
}

void	draw_sprites(t_table *table)
{
	int	i;

	order_sprites(table, table->enemies);
	i = -1;
	while (++i < N_ENEMIES)
		if (table->enemies[i].x != 0 && table->enemies[i].y != 0 && !table->enemies[i].dead)
			render_sprite(table, i);
	int y = -1;
	while (++y < table->height)
	{
		int x = -1;
		while (++x < table->width)
			mlx_put_pixel(table->mlx_3D, x, y, table->w_colors[y][x]);
	}
}
