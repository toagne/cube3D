/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:56:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/13 12:02:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite(t_table *table, t_enemy sp, int x)
{
	int	tex_x;
	int	tex_y;
	int	y;
	int	animation_x_offset;

	animation_x_offset = table->sprite_frames * 200;
	tex_x = ((x - sp.x_start) * (table->sprite_tx.width / 11))
		/ sp.screen_size + sp.tx_start_x + animation_x_offset;
	y = sp.y_start - 1;
	while (++y < sp.y_end)
	{
		tex_y = (y - sp.y_start) * (table->sprite_tx.height - 1)
			/ sp.screen_size + sp.tx_start_y;
		if (table->sprite_tx.colors[tex_y][tex_x] != 0x00000000)
		{
			if (table->sprite_tx.colors[tex_y][tex_x] != table->w_colors[y][x])
				table->w_colors[y][x] = table->sprite_tx.colors[tex_y][tex_x];
		}
	}
	if (table->sprite_frames == 10)
		table->sprite_frames = 0;
	else
		if (table->frame_counter % 20 == 0)
			table->sprite_frames++;
}

static void	select_texture_part_size_and_draw(t_table *table, t_enemy sp)
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

static void	render_sprite(t_table *table, int i)
{
	float	angle_diff;

	table->enemies[i].angle = atan2(table->enemies[i].dy,
			table->enemies[i].dx) * 180 / PI;
	if (table->enemies[i].angle < 0)
		table->enemies[i].angle += 360;
	angle_diff = table->enemies[i].angle - table->player_angle;
	if (angle_diff > 180)
		angle_diff -= 360;
	if (angle_diff < -180)
		angle_diff += 360;
	convert_sprite_sizes(table, angle_diff, &table->enemies[i]);
	select_texture_part_size_and_draw(table, table->enemies[i]);
}

static void	real_drawing(t_table *table)
{
	int	y;
	int	x;

	y = -1;
	while (++y < table->height)
	{
		x = -1;
		while (++x < table->width)
			mlx_put_pixel(table->mlx_raycast, x, y, table->w_colors[y][x]);
	}
	table->left_hand->instances[0].enabled = true;
	table->right_hand->instances[0].enabled = true;
	table->ball_image->instances[0].enabled = true;
}

void	draw_sprites(t_table *t)
{
	int	i;

	i = -1;
	while (++i < N_ENEMIES)
	{
		t->enemies[i].dx = t->enemies[i].x - t->player_x;
		t->enemies[i].dy = t->enemies[i].y - t->player_y;
		t->enemies[i].dist = sqrt((t->enemies[i].dx * t->enemies[i].dx)
				+ (t->enemies[i].dy * t->enemies[i].dy));
		if (t->enemies[i].dist < 30)
		{
			init_dynamic_data(t);
			display_gameover(t);
		}
	}
	order_sprites(t->enemies);
	i = -1;
	while (++i < N_ENEMIES)
		if (t->enemies[i].x != 0 && t->enemies[i].y != 0 && !t->enemies[i].dead)
			render_sprite(t, i);
	real_drawing(t);
}
