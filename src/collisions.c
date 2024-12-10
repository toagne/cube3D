/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:15:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 13:15:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	circle_rectangle_collision(float circle_x, float circle_y, int radius, int rect_x, int rect_y, int rect_size)
{
	// Find the closest point on the rectangle to the circle
	int	closest_x = fmax(rect_x, fmin(circle_x, rect_x + rect_size));
	int	closest_y = fmax(rect_y, fmin(circle_y, rect_y + rect_size));

	// Calculate distance from circle's center to closest point
	int	dx = circle_x - closest_x;
	int	dy = circle_y - closest_y;

	// Check if the distance is less than the circle's radius
	return (dx * dx + dy * dy) < (radius * radius);
}

int	wall_collision_w_circular_bumper(t_table *table, float new_x, float new_y, float boh_x, float boh_y, int radius)
{
	int	mpx;
	int	mpy;
	int	x;
	int	y;
	int	check_tile_x;
	int	check_tile_y;
	int	wall_x;
	int	wall_y;
	int	collision_detected;

	mpx = boh_x / T_SIZE;
	mpy = boh_y / T_SIZE;
	collision_detected = 0;
	// Check for collisions with walls ('1') and closed doors ('2')
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			check_tile_x = mpx + x;
			check_tile_y = mpy + y;
			if (check_tile_x >= 0 && check_tile_x < (int)table->columns && check_tile_y >= 0 && check_tile_y < (int)table->rows) 
			{
				wall_x = check_tile_x * T_SIZE;
				wall_y = check_tile_y * T_SIZE;

				if (table->map[check_tile_y][check_tile_x] == '1' || table->map[check_tile_y][check_tile_x] == '2' || table->map[check_tile_y][check_tile_x] == '4')
				{
					if (circle_rectangle_collision(new_x, new_y, radius, wall_x, wall_y, T_SIZE))
					{
						if (radius == 10 && table->map[check_tile_y][check_tile_x] == '2')
							table->map[check_tile_y][check_tile_x] = '3'; // Open the door
						if (radius == 10 && table->map[check_tile_y][check_tile_x] == '4')
						{
							init_dynamic_data(table);
							display_gamewon(table);
						}
						collision_detected = 1; // Block movement
					}
				}
			}
			x++;
		}
		y++;
	}
	// Handle door-closing logic for open doors ('3')
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			check_tile_x = mpx + x;
			check_tile_y = mpy + y;
			if (check_tile_x >= 0 && check_tile_x < (int)table->columns && check_tile_y >= 0 && check_tile_y < (int)table->rows) 
			{
				wall_x = check_tile_x * T_SIZE + T_SIZE / 2;
				wall_y = check_tile_y * T_SIZE + T_SIZE / 2;
				if (table->map[check_tile_y][check_tile_x] == '3')
				{
					// Calculate distance between the player and the door
					float dx = new_x - wall_x;
					float dy = new_y - wall_y;
					float dist = sqrt(dx * dx + dy * dy);
					// Check if any enemy is in the door's position
					int enemy_in_door = 0;
					int i = -1;
					while (++i < N_ENEMIES)
					{
						int enemy_tile_x = (int)(table->enemies[i].x / T_SIZE);
						int enemy_tile_y = (int)(table->enemies[i].y / T_SIZE);
						if (enemy_tile_x == check_tile_x && enemy_tile_y == check_tile_y)
						{
							enemy_in_door = 1;
							break;
						}
					}
					// Close the door only if the player is far enough and no enemy is present
					if (dist > T_SIZE * 1.5 && !enemy_in_door)
						table->map[check_tile_y][check_tile_x] = '2'; // Close the door
				}
			}
			x++;
		}
		y++;
	}
	return collision_detected;
}