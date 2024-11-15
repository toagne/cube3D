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

int	parse_rgb(t_table *table, char *color, char c)
{
	char **rgb_arr;
	int	number;
	int	i;
	int	*array;

	rgb_arr = ft_split(color, ',');
	free(color);
	if (!rgb_arr)
		return (1);
	i = 0;
	array = ft_calloc(3, sizeof(int));
	if (!array)
	{
		free_table(&rgb_arr);
		return (1);
	}
	while (rgb_arr[i])
	{
		number = ft_atoi(rgb_arr[i]);
		if ((rgb_arr[i][0] != '0' && number == 0) || number == -1)
		{
			free_table(&rgb_arr);
			return (1);
		}
		array[i] = number;
		++i;
	}
	if (c == 'F')
		table->f_color = array;
	else if (c == 'C')
		table->c_color = array;
	free_table(&rgb_arr);
	return (0);
}

int	check_element_identifier(t_table *table, char *line)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		temp = ft_strtrim(line, "NO");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		table->no_path_texture = temp1;
		return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		temp = ft_strtrim(line, "SO ");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		table->so_path_texture = temp1;
		return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		temp = ft_strtrim(line, "WE ");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		table->we_path_texture = temp1;
		return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		temp = ft_strtrim(line, "EA ");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		table->ea_path_texture = temp1;
		return (0);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		temp = ft_strtrim(line, "F");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		if (parse_rgb(table, temp1, 'F'))
			return (1);
		return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		temp = ft_strtrim(line, "C");
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		if (parse_rgb(table, temp1, 'C'))
			return (1);
		return (0);
	}
	return (1);
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
		ft_error("File could not be opened");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
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
			i += 1;
		}
		free(line);
		free(temp);
		line = get_next_line(fd);
		if (i == 6) // need to think about this when i us less than 6 it will be infinite loop
			break;
	}
	if (i == 6)
	{
		if (read_map(table, fd))
		{
			ft_error("Read failed or empty file");
			close(fd);
			return (1);
		}
		if (!validate_map(table))
		{
			free_map(table->map, table->columns);
			close(fd);
			return (1);
		}
		return (0);
	}
	else
		ft_error("invalid file");
	close(fd);
	return (1);
}
