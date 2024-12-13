/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:22:40 by giuls             #+#    #+#             */
/*   Updated: 2024/12/13 11:48:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pointer(t_table *table)
{
	t_line	line;

	line.x0 = table->width / 2 - table->height / 100;
	line.y0 = table->height / 2;
	line.x1 = table->width / 2 - table->height / 100 / 2;
	line.y1 = table->height / 2;
	line.color = 0xFFFFFFFF;
	draw_line(&line, table, 0, table->mlx_raycast);
	line.x0 = table->width / 2;
	line.y0 = table->height / 2 - table->height / 100;
	line.x1 = table->width / 2;
	line.y1 = table->height / 2 - table->height / 100 / 2;
	draw_line(&line, table, 0, table->mlx_raycast);
	line.x0 = table->width / 2 + table->height / 100;
	line.y0 = table->height / 2;
	line.x1 = table->width / 2 + table->height / 100 / 2;
	line.y1 = table->height / 2;
	draw_line(&line, table, 0, table->mlx_raycast);
	line.x0 = table->width / 2;
	line.y0 = table->height / 2 + table->height / 100;
	line.x1 = table->width / 2;
	line.y1 = table->height / 2 + table->height / 100 / 2;
	draw_line(&line, table, 0, table->mlx_raycast);
	mlx_put_pixel(table->mlx_raycast, table->width / 2,
		table->height / 2, 0xFFFFFFFF);
}

static float	calculate_angle_diff(t_table *table, float angle_to_enemy)
{
	float	angle_diff;

	angle_diff = table->player_angle - angle_to_enemy;
	if (angle_diff > 180)
		angle_diff -= 360;
	if (angle_diff < -180)
		angle_diff += 360;
	return (angle_diff);
}

static float	calculate_angle_to_enemy(int dx, int dy)
{
	float	angle_to_enemy;

	angle_to_enemy = atan2(dy, dx) * 180 / PI;
	if (angle_to_enemy < 0)
		angle_to_enemy += 360;
	if (angle_to_enemy >= 360)
		angle_to_enemy -= 360;
	return (angle_to_enemy);
}

static void	get_killing_zone(t_table *table, float *closest_ray,
	int *closest_enemy_index, int i)
{
	int		dx;
	int		dy;
	float	ray;
	float	angle_to_enemy;
	float	angle_diff;

	dx = table->enemies[i].x - table->player_x;
	dy = table->enemies[i].y - table->player_y;
	ray = sqrt((dx * dx) + (dy * dy));
	angle_to_enemy = calculate_angle_to_enemy(dx, dy);
	angle_diff = calculate_angle_diff(table, angle_to_enemy);
	if (fabs(angle_diff) <= 10)
	{
		check_vertical_lines(table, deg_to_rad(angle_to_enemy));
		check_horizontal_lines(table, deg_to_rad(angle_to_enemy));
		chose_shortest_ray(table);
		if (ray <= table->ray.f_v && ray < *closest_ray)
		{
			*closest_ray = ray;
			*closest_enemy_index = i;
		}
	}
}

void	kill_sprite(t_table *table)
{
	int		i;
	float	closest_ray;
	int		closest_enemy_index;

	closest_enemy_index = -1;
	closest_ray = FLT_MAX;
	i = -1;
	while (++i < N_ENEMIES)
	{
		if (table->enemies[i].dead)
			continue ;
		if (table->enemies[i].x == 0 && table->enemies[i].y == 0)
			table->enemies[i].dead = 1;
		get_killing_zone(table, &closest_ray, &closest_enemy_index, i);
	}
	if (closest_enemy_index != -1)
	{
		table->enemies[closest_enemy_index].dead = 1;
		table->enemies[closest_enemy_index].x = 0;
		table->enemies[closest_enemy_index].y = 0;
		table->kill = 0;
	}
}
