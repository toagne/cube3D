/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:24:40 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 12:47:42 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	get_final_val(t_table *t, char side, float side_t_x, float side_t_y)
{
	int		p_x;
	int		p_y;

	p_x = t->player_x;
	p_y = t->player_y;
	if (side == 'v')
	{
		t->ray.v_v = sqrt((p_x - side_t_x) * (p_x - side_t_x)
				+ (p_y - side_t_y) * (p_y - side_t_y));
		t->ray.v_x = side_t_x;
		t->ray.v_y = side_t_y;
	}
	else if (side == 'h')
	{
		t->ray.h_v = sqrt((p_x - side_t_x) * (p_x - side_t_x)
				+ (p_y - side_t_y) * (p_y - side_t_y));
		t->ray.h_x = side_t_x;
		t->ray.h_y = side_t_y;
	}
}

static void	check_if_wall(t_table *t, float side_t_x, float side_t_y, char side)
{
	int	map_x;
	int	map_y;

	while (side_t_x > 0 && side_t_y > 0 && side_t_x < T_SIZE * t->columns
		&& side_t_y < T_SIZE * t->rows)
	{
		map_x = side_t_x / T_SIZE;
		map_y = side_t_y / T_SIZE;
		if (t->map[map_y][map_x] == '1' || t->map[map_y][map_x] == '2'
		|| t->map[map_y][map_x] == '4')
			break ;
		else
		{
			side_t_x += t->tile_step_x;
			side_t_y += t->tile_step_y;
		}
	}
	get_final_val(t, side, side_t_x, side_t_y);
}

void	check_horizontal_lines(t_table *t, float angle)
{
	float	h_side_t_x;
	float	h_side_t_y;

	t->ray.h_v = 100000;
	if (angle > 0 && angle < PI)
	{
		h_side_t_y = (int)(t->player_y / T_SIZE) * T_SIZE + T_SIZE;
		h_side_t_x = -(t->player_y - h_side_t_y) / tan(angle) + t->player_x;
		t->tile_step_y = T_SIZE;
		t->tile_step_x = T_SIZE / tan(angle);
	}
	else
	{
		h_side_t_y = (int)(t->player_y / T_SIZE) * T_SIZE - 0.0001;
		h_side_t_x = -(t->player_y - h_side_t_y) / tan(angle) + t->player_x;
		t->tile_step_y = -T_SIZE;
		t->tile_step_x = -(T_SIZE / tan(angle));
	}
	check_if_wall(t, h_side_t_x, h_side_t_y, 'h');
}

void	check_vertical_lines(t_table *t, float angle)
{
	float	v_side_t_x;
	float	v_side_t_y;

	t->ray.v_v = 100000;
	if (angle > 3 * PI / 2 || angle < PI / 2)
	{
		v_side_t_x = (int)(t->player_x / T_SIZE) * T_SIZE + T_SIZE;
		v_side_t_y = -(t->player_x - v_side_t_x) * tan(angle) + t->player_y;
		t->tile_step_x = T_SIZE;
		t->tile_step_y = T_SIZE * tan(angle);
	}
	else
	{
		v_side_t_x = (int)(t->player_x / T_SIZE) * T_SIZE - 0.0001;
		v_side_t_y = -(t->player_x - v_side_t_x) * tan(angle) + t->player_y;
		t->tile_step_x = -T_SIZE;
		t->tile_step_y = -T_SIZE * tan(angle);
	}
	check_if_wall(t, v_side_t_x, v_side_t_y, 'v');
}
