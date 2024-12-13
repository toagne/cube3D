/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:37:42 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 12:00:20 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_lines(int fd, char ***map, t_table *table, char *line)
{
	int		ln;
	char	*trimmed;

	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (line)
			trimmed = ft_strtrim(line, "\n");
		if (!*map || !trimmed)
		{
			free_map(map, ln);
			free(trimmed);
			free(line);
			return (0);
		}
		(*map)[ln] = trimmed;
		if (line)
			++ln;
		free(line);
	}
	table->rows = ln;
	(*map)[ln] = NULL;
	return (1);
}

static char	check_player_dir(char dir)
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

static void	set_player_position(t_table *table)
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

int	read_map(t_table *table, int fd, char *line)
{
	char	**map;

	map = ft_calloc(1, sizeof(char *));
	if (!map)
		return (1);
	map[0] = line;
	if (!read_lines(fd, &map, table, line))
		return (1);
	if (fill_ones_to_map(&map))
	{
		free_table(&map);
		return (1);
	}
	table->columns = ft_strlen(map[0]);
	table->map = map;
	set_player_position(table);
	return (0);
}
