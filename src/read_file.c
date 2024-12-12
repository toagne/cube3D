/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:29:28 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 09:49:37 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	verify_elements_ids(t_table *table)
{
	if (!table->f_color)
		return (1);
	if (!table->c_color)
		return (1);
	if (!table->ws_path_texture)
		return (1);
	if (!table->so_path_texture)
		return (1);
	if (!table->es_path_texture)
		return (1);
	if (!table->no_path_texture)
		return (1);
	return (0);
}

int	verify_and_read_map(t_table *table, int fd, char *line)
{
	if (!verify_elements_ids(table) && !table->duplicate_id)
	{
		if (read_map(table, fd, line))
		{
			ft_error("Read failed or empty file");
			close(fd);
			return (1);
		}
		if (!validate_map(table))
		{
			free_map(table->map, table->rows);
			close(fd);
			return (1);
		}
		return (0);
	}
	else
	{
		if (table->duplicate_id)
			ft_error("duplicate ids in the file");
		else
			ft_error("Invalid element identifiers");
		return (1);
	}
}

int	process_file_lines(int fd, t_table *table)
{
	char	*line;
	char	*trimnl;
	int		result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_line(line, table, &trimnl);
		if (result == 1)
			return (1);
		if (result == 2)
			break ;
		line = get_next_line(fd);
	}
	if (!verify_and_read_map(table, fd, trimnl))
		return (0);
	return (1);
}

int	read_file(t_table *table)
{
	int	fd;
	int	result;

	fd = open_file(table->filename);
	if (fd == -1)
		return (1);
	result = process_file_lines(fd, table);
	close(fd);
	return (result);
}
