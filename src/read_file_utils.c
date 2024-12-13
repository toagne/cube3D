/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:55:33 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 08:41:29 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	open_file(const char *filename, t_table *table)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("File could not be opened", table);
	return (fd);
}

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != 'N' && *line != 'S' && *line != 'E' && *line != 'W'
			&& *line != '0' && *line != '1' && *line != ' ')
			return (0);
		++line;
	}
	return (1);
}

int	is_only_newline(char *line)
{
	if (ft_strlen(line) == 1 && *line == '\n')
		return (1);
	return (0);
}
