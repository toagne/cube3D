/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:32:35 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 17:19:00 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_pos_valid(t_table *t, int x_tile, int y_tile)
{
	if (abs(x_tile - t->player_col) > (int)t->columns / 2
		&& abs(y_tile - t->player_row) > (int)t->rows / 2)
	{
		if ((y_tile + 1 < (int)t->rows && t->map[y_tile + 1][x_tile] == '0')
			|| (y_tile - 1 >= 0 && t->map[y_tile - 1][x_tile] == '0') ||
			(x_tile + 1 < (int)t->columns && t->map[y_tile][x_tile + 1] == '0')
			|| (x_tile - 1 >= 0 && t->map[y_tile][x_tile - 1] == '0'))
		{
			t->map[y_tile][x_tile] = '4';
			return (1);
		}
	}
	return (0);
}

void	get_random_win_spot(t_table *table)
{
	int	x_tile;
	int	y_tile;

	y_tile = -1;
	while (++y_tile < (int)table->rows)
	{
		x_tile = -1;
		while (++x_tile < (int)table->columns)
		{
			if (table->map[y_tile][x_tile] == '1')
				if (is_pos_valid(table, x_tile, y_tile))
					return ;
		}
	}
}

int	is_position_valid(t_table *table, size_t x, size_t y)
{
	int	e_y;
	int	e_x;

	if (table->map[y][x] != '0')
		return (0);
	e_y = table->player_row - 1;
	while (e_y <= table->player_row + 1)
	{
		e_x = table->player_col - 1;
		while (e_x <= table->player_col + 1)
		{
			if (e_x == (int)x && e_y == (int)y)
				return (0);
			e_x++;
		}
		e_y++;
	}
	return (1);
}

int	max_attempt_reached(int attempts)
{
	if (attempts == 20)
	{
		printf("Warning: Unable to place enemies\n");
		return (1);
	}
	return (0);
}

void	init_enemies(t_table *table)
{
	size_t	x;
	size_t	y;
	int		attempts;
	int		i;

	i = -1;
	while (++i < N_ENEMIES)
	{
		attempts = -1;
		while (++attempts < 20)
		{
			y = my_rand(table) % table->rows;
			x = my_rand(table) % table->columns;
			if (is_position_valid(table, x, y))
			{
				table->enemies[i].x = x * T_SIZE + T_SIZE / 2;
				table->enemies[i].y = y * T_SIZE + T_SIZE / 2;
				break ;
			}
		}
		if (max_attempt_reached(attempts))
			break ;
	}
}
