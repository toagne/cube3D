/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:37:42 by omartela          #+#    #+#             */
/*   Updated: 2024/11/14 10:48:29 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

void	free_map(char **map, size_t i)
{
	while (i > 0)
	{
		i--;
		free(map[i]);
	}
	free(map);
}

static int	check_empty_file(int fd, char **line, char **map)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		free(map);
		ft_error("Read failed or empty file");
		return (0);
	}
	return (1);
}

static int	read_lines(int fd, char ***map, t_table *table)
{
	char	*line;
	int		ln;
	char	*trimmed;

	line = NULL;
	if (!check_empty_file(fd, &line, *map))
		return (0);
	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
	{
		free(map);
		return (0);
	}
	(*map)[0] = trimmed;
	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (line)
			trimmed = ft_strtrim(line, "\n");
		if (!*map || !trimmed)
		{
			free_map(*map, ln);
			free(line);
			line = NULL;
			return (0);
		}
		(*map)[ln] = trimmed;
		if (line)
			++ln;
		free(line);
	}
	table->rows = ln;
	return (1);
}

int	check_player_dir(char dir)
{
	if (dir == 'N')
		return (1);
	else if (dir == 'W')
		return (1);
	else if (dir == 'S')
		return (1);
	else if (dir == 'E')
		return (1);
	return (0);
}

void set_player_position(t_table *table)
{
	size_t	player_pos_x;
	size_t	player_pos_y;

	player_pos_y = 0;
	while (player_pos_y < table->rows)
	{
		player_pos_x = 0;
		while (player_pos_x < table->columns)
		{
			if (check_player_dir(table->map[player_pos_y][player_pos_x]))
			{
				table->player_row = player_pos_y;
				table->player_col = player_pos_x;
			}
			++player_pos_x;
		}
		++player_pos_y;
	}
	printf("%d x %d\n", table->player_col, table->player_row);
	table->player_x = (float)table->player_col * T_SIZE - T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE - T_SIZE / 2;
	printf("%f x %f\n", table->player_x, table->player_y);
}

int	read_map(t_table *table)
{
	int		fd;
	char	**map;

	fd = open(table->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error("File could not be opened");
		return (0);
	}
	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (0);
	}
	if (!read_lines(fd, &map, table))
	{
		close(fd);
		return (0);
	}
	table->columns = ft_strlen(map[0]);
	table->map = map;
	close(fd);
	set_player_position(table);
	return (1);
}
