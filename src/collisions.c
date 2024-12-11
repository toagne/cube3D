/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:15:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 11:35:57 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	circle_rectangle_collision(float circle_x, float circle_y,
	t_collision *coll_data)
{
	int	closest_x;
	int	closest_y;
	int	dx;
	int	dy;

	closest_x = fmax(coll_data->wall_x,
			fmin(circle_x, coll_data->wall_x + T_SIZE));
	closest_y = fmax(coll_data->wall_y,
			fmin(circle_y, coll_data->wall_y + T_SIZE));
	dx = circle_x - closest_x;
	dy = circle_y - closest_y;
	return ((dx * dx + dy * dy) < (coll_data->r * coll_data->r));
}

void	boh(t_table *t, float new_x, float new_y, t_collision *coll_data)
{
	int	t_x;
	int	t_y;

	t_x = coll_data->check_tile_x;
	t_y = coll_data->check_tile_y;
	if (t_x >= 0 && t_x < (int)t->columns && t_y >= 0 && t_y < (int)t->rows)
	{
		coll_data->wall_x = t_x * T_SIZE;
		coll_data->wall_y = t_y * T_SIZE;
		if (t->map[t_y][t_x] == '1' || t->map[t_y][t_x] == '2'
			|| t->map[t_y][t_x] == '4')
		{
			if (circle_rectangle_collision(new_x, new_y, coll_data))
			{
				if (coll_data->r == 10 && t->map[t_y][t_x] == '2')
					t->map[t_y][t_x] = '3';
				if (coll_data->r == 10 && t->map[t_y][t_x] == '4')
				{
					init_dynamic_data(t);
					display_gamewon(t);
				}
				coll_data->collision_detected = 1;
			}
		}
	}
}

void	boh_1(t_table *table, float new_x, float new_y, t_collision *coll_data)
{
	float	dx;
	float	dy;
	float	dist;
	int		enemy_in_door;
	int		i;

	dx = new_x - coll_data->wall_x;
	dy = new_y - coll_data->wall_y;
	dist = sqrt(dx * dx + dy * dy);
	enemy_in_door = 0;
	i = -1;
	while (++i < N_ENEMIES)
	{
		coll_data->sp_tile_x = (int)(table->enemies[i].x / T_SIZE);
		coll_data->sp_tile_y = (int)(table->enemies[i].y / T_SIZE);
		if (coll_data->sp_tile_x == coll_data->check_tile_x
			&& coll_data->sp_tile_y == coll_data->check_tile_y)
		{
			enemy_in_door = 1;
			break ;
		}
	}
	if (dist > T_SIZE * 1.5 && !enemy_in_door)
		table->map[coll_data->check_tile_y][coll_data->check_tile_x] = '2';
}

void	door_closing(t_table *t, float new_x, float new_y, t_collision *c_data)
{
	int	x;
	int	y;

	y = -2;
	while (++y <= 1)
	{
		x = -2;
		while (++x <= 1)
		{
			c_data->check_tile_x = c_data->mpx + x;
			c_data->check_tile_y = c_data->mpy + y;
			if (c_data->check_tile_x >= 0
				&& c_data->check_tile_x < (int)t->columns
				&& c_data->check_tile_y >= 0
				&& c_data->check_tile_y < (int)t->rows)
			{
				c_data->wall_x = c_data->check_tile_x * T_SIZE + T_SIZE / 2;
				c_data->wall_y = c_data->check_tile_y * T_SIZE + T_SIZE / 2;
				if (t->map[c_data->check_tile_y][c_data->check_tile_x] == '3')
					boh_1(t, new_x, new_y, c_data);
			}
		}
	}
}

int	wall_coll_w_circular_bumper(t_table *table, float new_x,
	float new_y, t_collision *coll_data)
{
	int	x;
	int	y;

	coll_data->mpx = coll_data->x0 / T_SIZE;
	coll_data->mpy = coll_data->y0 / T_SIZE;
	coll_data->collision_detected = 0;
	y = -2;
	while (++y <= 1)
	{
		x = -2;
		while (++x <= 1)
		{
			coll_data->check_tile_x = coll_data->mpx + x;
			coll_data->check_tile_y = coll_data->mpy + y;
			boh(table, new_x, new_y, coll_data);
		}
	}
	door_closing(table, new_x, new_y, coll_data);
	return (coll_data->collision_detected);
}
