/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:44:07 by omartela          #+#    #+#             */
/*   Updated: 2024/12/07 00:02:18 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int validate_walls_sides(t_table *table)
{
	size_t	col;
	size_t	row;

	row = 0;
	col = 0;
	while (row < table->rows)
	{
		if (table->map[row][col] != '1')
		{
			ft_error("Map has invalid characters at sides");
			return (0);
		}
		++row;
	}
	row = 0;
	col = table->columns - 1;
	while (row < table->rows)
	{
		if (table->map[row][col] != '1')
		{
			ft_error("Map has invalid characters at sides");
			return (0);
		}
		++row;
	}
	return (1);
}

static int validate_walls_top_bot(t_table *table)
{
	size_t	col;

	col = 0;
	while (col < table->columns)
	{
		if (table->map[0][col] != '1' && table->map[0][col] != ' ')
		{
			printf("we are here 2 %zu\n", col);
			ft_error("Map has invalid characters top");
			return (0);
		}
		++col;
	}
	col = 0;
	while (col < table->columns)
	{
		if (table->map[table->rows - 1][col] != '1' && table->map[table->rows - 1][col] != ' ')
		{
			printf("we are here 1\n");
			ft_error("Map has invalid characters bot");
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
