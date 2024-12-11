/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:22:40 by giuls             #+#    #+#             */
/*   Updated: 2024/12/10 17:42:15 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void    get_killing_zone(t_table *table, t_enemy sp, float *angle_diff)
{
    int		dx;
	int		dy;
    float	ray;
    float	angle_to_enemy;

    dx = sp.x - table->player_x;
	dy = sp.y - table->player_y;
	ray = sqrt((dx * dx) + (dy * dy));
    angle_to_enemy = atan2(dy, dx) * 180 / PI;
    if (angle_to_enemy < 0)
        angle_to_enemy += 360;
    if (angle_to_enemy >= 360)
        angle_to_enemy -= 360;
    *angle_diff = table->player_angle - angle_to_enemy;
	if (*angle_diff > 180)
		*angle_diff -= 360;
	if (*angle_diff < -180)
		*angle_diff += 360;
} */

void	kill_sprite(t_table *table)
{
	int		i;
	int		dx;
	int		dy;
	float	angle_to_enemy;
	float	angle_diff;
	float	ray;
	float	closest_ray;
	int		closest_enemy_index;

	closest_enemy_index = -1;
	closest_ray = FLT_MAX;
	i = -1;
	while (++i < N_ENEMIES)
	{
		if (table->enemies[i].dead)
			continue ;
		dx = table->enemies[i].x - table->player_x;
		dy = table->enemies[i].y - table->player_y;
		ray = sqrt((dx * dx) + (dy * dy));
		angle_to_enemy = atan2(dy, dx) * 180 / PI;
		if (angle_to_enemy < 0)
			angle_to_enemy += 360;
		if (angle_to_enemy >= 360)
			angle_to_enemy -= 360;
		angle_diff = table->player_angle - angle_to_enemy;
		if (angle_diff > 180)
			angle_diff -= 360;
		if (angle_diff < -180)
			angle_diff += 360;
        //get_killing_zone(table, table->enemies[i], &angle_diff);
		if (fabs(angle_diff) <= 10)
		{
			check_vertical_lines(table, deg_to_rad(angle_to_enemy));
			check_horizontal_lines(table, deg_to_rad(angle_to_enemy));
			chose_shortest_ray(table);
			if (ray <= table->ray.f_v && ray < closest_ray)
			{
				closest_ray = ray;
				closest_enemy_index = i;
			}
		}
	}
	if (closest_enemy_index != -1)
	{
		int i = closest_enemy_index;
		table->enemies[i].dead = 1;
		table->enemies[i].x = 0;
		table->enemies[i].y = 0;
		table->kill = 0;
	}
}

void    actions(t_table *table)
{
    if (!table->is_attacking)
		insert_fireball(table);
	else
	{
		animate_attack(table);
		if (table->kill)
			kill_sprite(table);
	}
}
