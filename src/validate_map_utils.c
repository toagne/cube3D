/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:29:01 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 08:40:14 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	validate_file_ext(char *file, t_table *table)
{
	char	*ext;

	ext = NULL;
	ext = ft_strrchr(file, '.');
	if (ext == NULL)
	{
		ft_error("Invalid file name or extension", table);
		return (0);
	}
	if (ft_strncmp(ext, ".cub", 5) != 0)
	{
		ft_error("Invalid file name or extension", table);
		return (0);
	}
	return (1);
}

static void	check_character(t_table *table, int c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		table->player += 1;
}

static int	validate_map_char(char c)
{
	if (ft_strchr("NSWE 10", c))
		return (1);
	return (0);
}

static int	validate_map_chars(t_table *table)
{
	size_t	col;
	size_t	row;

	row = 0;
	while (row < table->rows)
	{
		col = 0;
		while (col < table->columns)
		{
			if (!validate_map_char(table->map[row][col]))
			{
				ft_error("Map has invalid characters", table);
				return (0);
			}
			check_character(table, table->map[row][col]);
			++col;
		}
		++row;
	}
	if (table->player != 1)
	{
		ft_error("Too few or too many players", table);
		return (0);
	}
	return (1);
}

int	validate_map_chars_and_ext(t_table *table)
{
	if (!validate_file_ext(table->filename, table))
		return (0);
	if (!validate_map_chars(table))
		return (0);
	return (1);
}
