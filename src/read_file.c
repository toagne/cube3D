/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:29:28 by omartela          #+#    #+#             */
/*   Updated: 2024/12/07 00:04:07 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_skipwhitespace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == '\n')
		++str;
	return (str);
}

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' &&
		*line != '0' && *line != '1' && *line != ' ')
			return (0);
		++line;
	}
	return (1);
}

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
int	is_only_newline(char *line)
{
	if (ft_strlen(line) == 1 && *line == '\n')
		return (1);
	return (0);
}

int	verify_file_reading(t_table *table, int fd, char *line)
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

int	open_file(const char *filename)
{
	int fd;
 
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("File could not be opened");
	return (fd);
}

int	prepare_line(char *line, char **trimnl)
{
	if (is_only_newline(line))
	{
		free(line);
		return (0);
	}
	*trimnl = ft_strtrim(line, "\n");
	if (!*trimnl)
	{
		free(line);
		return (1);
	}
	if (is_map_line(*trimnl))
	{
		free(line);
		return (2);
	}
	return (3);
}


int	process_trimmed_line(char *line, char *trimnl, t_table *table)
{
	char	*temp;

	temp = ft_skipwhitespace(trimnl);
	if (check_element_ids(table, temp))
	{
		ft_error("Set element texture failed");
		free(line);
		free(trimnl);
		return (1);
	}
	free(line);
	free(trimnl);
	return (0);
}

int	process_line(char *line, t_table *table, char **trimnl)
{
	int result;

	result = prepare_line(line, trimnl);
	if (result != 3)
		return (result);
	return (process_trimmed_line(line, *trimnl, table));
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

	if (!verify_file_reading(table, fd, trimnl))
		return (0);
	return (1);
}

int	read_file(t_table *table)
{
	int	fd;
	int	result;

	fd = open_file(table->filename);
	if (fd == -1)
		return 1;
	result = process_file_lines(fd, table);
	close(fd);
	return (result);
}

