/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:41:29 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/04 09:30:07 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

void	get_monitor_size(int *width, int *height)
{
	mlx_t	*temp;
	int32_t w;
	int32_t h;

	temp = mlx_init(1, 1, "", false);
	if (!temp)
	{
		;//error
	}
	mlx_get_monitor_size(0, &w, &h);
	mlx_terminate(temp);
	*width = w / 1.5;
	*height = h / 1.5;
}

float	deg_to_rad(float deg)
{
	return ((float)deg / 180 * PI);
}

void	draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color)
{
	const double step = 0.01;
	double angle;
	int x;
	int y;

	angle = 0;
	while (angle <= 2 * PI)
	{
		x = x_center + (int)(radius * cos(angle));
		y = y_center + (int)(radius * sin(angle));
		mlx_put_pixel(image, x, y, color);
		angle += step;
	}
}
// draw circle should not be used

int	my_rand(t_table *table)
{
	long	lcg_a;
	long	lcg_c;
	long	lcg_m;

	lcg_a = 1103515245;
	lcg_c = 12345;
	lcg_m = 2147483648;
	table->lcg_seed = (lcg_a * table->lcg_seed + lcg_c) % lcg_m;
	return (table->lcg_seed);
}

/* int check_distance(t_table *table, int x, int y, int distance) 
{
	if (abs(table->player_col - x) >= distance || abs(table->player_row - y) >= distance)
		return (1);
	return (0);
}
 */
void init_enemies(t_table *table) 
{
	size_t	x;
	size_t	y;
	int		limit;
	int		i;
	int		flag;

	x = 0;
	y = 0;
	limit = 0;
	i = 0;
	flag = 0;
	// srand(time(NULL));
	while (i < N_ENEMIES)
	{
		limit = -1;
		while (++limit < 20)
		{
			flag = 0;
			// y = rand() % table->rows;
			// x = rand() % table->columns;
			y = my_rand(table) % table->rows;
			x = my_rand(table) % table->columns;
			// printf("y = %zu, x = %zu\n", y, x);
			int e_y = table->player_row - 1;
			int e_x = table->player_col - 1;
			// printf("e_y = %d\n", e_y);
			// printf("player row = %d\n", table->player_row);
			while (e_y <= table->player_row + 1)
			{
				e_x = table->player_col - 1;
				while (e_x <= table->player_col + 1)
				{
					// printf("y = %zu, x = %zu\n", y, x);
					// printf("e_y = %d, e_x = %d\n\n", e_y, e_x);
					if (e_x == (int)x && e_y == (int)y)
					{
						flag = 1;
						break ;
					}
					e_x++;
				}
				e_y++;
			}
			if (table->map[y][x] == '0' && !flag)
			{
				// printf("spawn position found \n");
				table->enemies[i].x = x * T_SIZE + T_SIZE / 2;
				table->enemies[i].y = y * T_SIZE + T_SIZE / 2;
				// i++;
				// printf("spawn y = %d, spawn x = %d\n", table->e_spawn_pos_y, table->e_spawn_pos_x);
				break ;
			}
		}
		if (limit == 20)
			printf("No valid enemy spawn position found \n");
		i++;
	}
}

long	get_time(char type)
{
	struct timeval	tv;

	// if (gettimeofday(&tv, NULL) == -1)
	// 	return (return_error_int("gettimeofday failed\n"));
	gettimeofday(&tv, NULL);
	if (type == 'a')
	{
		return (tv.tv_sec + tv.tv_usec / 1000000);
	}
	else if (type == 'b')
	{
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	}
	else
		return (0);
}
