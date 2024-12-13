/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:44:07 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 10:51:05 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_sides(t_table *table, size_t row, size_t col)
{
	while (row < table->rows)
	{
		if (table->map[row][col] != '1')
		{
			ft_error("Map has invalid characters at sides", table);
			return (0);
		}
		++row;
	}
	return (1);
}

static int	validate_walls_sides(t_table *table)
{
	size_t	col;
	size_t	row;

	row = 0;
	col = 0;
	if (!check_sides(table, row, col))
		return (0);
	row = 0;
	col = table->columns - 1;
	if (!check_sides(table, row, col))
		return (0);
	return (1);
}

static int	validate_walls_top_bot(t_table *table)
{
	size_t	col;

	col = 0;
	while (col < table->columns)
	{
		if (table->map[0][col] != '1' && table->map[0][col] != ' ')
		{
			ft_error("Map has invalid characters top", table);
			return (0);
		}
		++col;
	}
	col = 0;
	while (col < table->columns)
	{
		if (table->map[table->rows - 1][col] != '1' &&
				table->map[table->rows - 1][col] != ' ')
		{
			ft_error("Map has invalid characters bot", table);
			return (0);
		}
		++col;
	}
	return (1);
}

int	validate_map(t_table *table)
{
	if (!validate_map_chars_and_ext(table))
		return (0);
	if (!validate_walls_sides(table))
		return (0);
	if (!validate_walls_top_bot(table))
		return (0);
	return (1);
}
