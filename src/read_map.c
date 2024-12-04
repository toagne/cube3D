/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:37:42 by omartela          #+#    #+#             */
/*   Updated: 2024/11/20 18:17:58 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_lines(int fd, char ***map, t_table *table)
{
	int		ln;
	char	*line;
	char	*trimmed;

	ln = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		trimmed = ft_strtrim(line, "\n");
		if (!*map || !trimmed)
		{
			free_map(*map, ln);
			free(line);
			return (0);
		}
		(*map)[ln] = trimmed;
		++ln;
		free(line);
		line = get_next_line(fd);
	}
	table->rows = ln;
	(*map)[ln] = NULL;
	return (1);
}

char	check_player_dir(char dir)
{
	if (dir == 'N')
		return ('N');
	else if (dir == 'W')
		return ('W');
	else if (dir == 'S')
		return ('S');
	else if (dir == 'E')
		return ('E');
	return ('\0');
}

void set_player_position(t_table *table)
{
	size_t	player_pos_x;
	size_t	player_pos_y;
	char	dir;

	player_pos_y = 0;
	dir = 0;
	while (player_pos_y < table->rows)
	{
		player_pos_x = 0;
		while (player_pos_x < table->columns)
		{
			dir = check_player_dir(table->map[player_pos_y][player_pos_x]);
			if (dir)
			{
				table->player_dir = dir;
				table->player_row = player_pos_y;
				table->player_col = player_pos_x;
			}
			++player_pos_x;
		}
		++player_pos_y;
	}
	table->player_x = (float)table->player_col * T_SIZE + T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE + T_SIZE / 2;
}

int	find_length_of_longest_line(char **map)
{
	int	i;
	int	len;
	int	current_len;

	i = 0;
	current_len = 0;
	len = 0;
	if (!map || !*map)
		return (-1);
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len > len)
			len = current_len;
		++i;
	}
	return (len);
}

char	*fill_spaces(int len, char *line)
{
	char	*newline;
	int		src_len;

	newline = malloc((len + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	ft_strlcpy(newline, line, len + 1);
	src_len = ft_strlen(line);
	while (src_len < len)
	{
		newline[src_len] = '1';
		src_len++;
	}
	newline[len] = '\0';
	return (newline);
}

int fill_spaces_to_map(char ***map)
{
	size_t	i;
	size_t	len;
	char *temp;

	i = 0;
	len = find_length_of_longest_line(*map);
	while ((*map)[i])
	{
		if (ft_strlen((*map)[i]) != len)
		{
			temp = fill_spaces(len, (*map)[i]);
			if (!temp)
				return (1);
			free((*map)[i]);
			(*map)[i] = temp;
		}
		++i;
	}
	return (0);
}

int	read_map(t_table *table, int fd, char *line)
{
	char	**map;

	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (1);
	}
	map[0] = line;
	if (!read_lines(fd, &map, table))
	{
		close(fd);
		return (1);
	}
	if (fill_spaces_to_map(&map))
	{
		free_table(&map);
		return (0);
	}
	table->columns = ft_strlen(map[0]);
	table->map = map;
	set_player_position(table);
	return (0);
}
