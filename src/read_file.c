/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:29:28 by omartela          #+#    #+#             */
/*   Updated: 2024/11/15 09:18:39 by omartela         ###   ########.fr       */
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

int	check_element_identifier(t_table *table, char *line)
{
	char	*temp;

	if (ft_strncmp(line, "NO", 3))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->no_path_texture = temp;
		return (1);
	}
	else if (ft_strncmp(line, "SO", 3))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->so_path_texture = temp;
		return (1);
	}
	else if (ft_strncmp(line, "WE", 3))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->we_path_texture = temp;
		return (1);
	}
	else if (ft_strncmp(line, "EA", 3))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->ea_path_texture = temp;
		return (1);
	}
	else if (ft_strncmp(line, "F", 2))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->we_path_texture = temp;
		return (1);
	}
	else if (ft_strncmp(line, "C", 2))
	{
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (0);
		table->we_path_texture = temp;
		return (1);
	}
	return (0);
}

int	read_file(t_table *table)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*temp1;
	int		i;

	i = 0;
	fd = open(table->filename, O_RDONLY);
	if (fd == -1)
	{
		error("File could not be opened");
		return (1);
	}
	line = get_next_line(fd);
	while (!line)
	{
		temp = ft_strtrim(line, "\n");
		if (!temp)
		{
			free(line);
			return (1);
		}
		temp1 = ft_skipwhitespace(temp);
		if (!check_element_identifier(table, temp1))
		{
			ft_error("failed to set element\n");	 
		}
		i += 1;
		free(line);
		free(temp);
	}
}
