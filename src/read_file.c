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

void	check_duplicate_color(t_table *table, int *array, char c)
{
	if (c == 'F')
	{
		if (!table->f_color)
			table->f_color = array;
		else
			table->duplicate_id = 1;
	}
	else if (c == 'C')
	{
		if (!table->c_color)
			table->c_color = array;
		else
			table->duplicate_id = 1;
	}
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
	check_duplicate_color(table, array, c);
	free_table(&rgb_arr);
	return (0);
}

void	set_element_texture(t_table *table, char *str, char *texture)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
	{
		if (!table->no_path_texture)
			table->no_path_texture = texture;
		else
			table->duplicate_id = 1;
	}
	else if (ft_strncmp(str, "SO ", 3) == 0)
	{
		if (!table->so_path_texture)
			table->so_path_texture = texture;
		else
			table->duplicate_id = 1;
	}
	else if (ft_strncmp(str, "WE ", 3) == 0)
	{
		if (!table->ws_path_texture)
			table->ws_path_texture = texture;
		else
			table->duplicate_id = 1;
	}
	else if (ft_strncmp(str, "EA ", 3) == 0)
	{
		if (!table->es_path_texture)
			table->es_path_texture = texture;
		else
			table->duplicate_id = 1;
	}
}

int	check_element_id(t_table *table, char *line, char *str)
{
	char	*temp;
	char	*temp1;
	temp = NULL;
	if (ft_strncmp(line, str, 3) == 0)
	{
		temp = ft_strtrim(line, str);
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		set_element_texture(table, str, temp1);
		return (0);
	}
	else if (ft_strncmp(line, str, 2) == 0)
	{
		temp = ft_strtrim(line, str);
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp); 
		if (parse_rgb(table, temp1, str[0]))
			return (1);
		return (0);
	}
	return (1);
}

int	check_element_ids(t_table *table, char *line)
{
	if (!check_element_id(table, line, "NO "))
		return (0);
	else if (!check_element_id(table, line, "SO "))
		return (0);
	else if (!check_element_id(table, line, "WE "))
		return (0);
	else if (!check_element_id(table, line, "EA "))
		return (0);
	else if (!check_element_id(table, line, "F "))
		return (0);
	else if (!check_element_id(table, line, "C "))
		return (0);
	return (1);
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
	printf("%s \n", line);
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
		if (is_only_newline(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			temp = ft_strtrim(line, "\n");
			if (!temp)
			{
				free(line);
				return (1);
			}
			if (is_map_line(temp))
			{
				free(line);
				break;
			}
			temp1 = ft_skipwhitespace(temp);
			if (!check_element_ids(table, temp1))
			{ 
				i += 1;
			}
			free(line);
			free(temp);
			line = get_next_line(fd);
		}
	}
	if (!verify_elements_ids(table) && !table->duplicate_id)
	{
		if (read_map(table, fd, temp))
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
			ft_error("invalid file");
	}
	close(fd);
	return (1);
}
