/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:37:42 by omartela          #+#    #+#             */
/*   Updated: 2024/11/14 09:49:15 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

static int	check_empty_file(int fd, char **line, char **map)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		free(map);
		error("Read failed or empty file");
		return (0);
	}
	return (1);
}

static int	read_lines(int fd, char ***map, t_table *table)
{
	char	*line;
	int		ln;

	line = NULL;
	if (!check_empty_file(fd, &line, *map))
		return (0);
	(*map)[0] = line;
	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (!*map)
		{
			free_map(*map, ln);
			free(line);
			line = NULL;
			return (0);
		}
		(*map)[ln] = line;
		if (line)
			++ln;
	}
	table->rows = ln;
	return (1);
}

int	read_map(t_table *table)
{
	int		fd;
	char	**map;

	fd = open(table->filename, O_RDONLY);
	if (fd == -1)
	{
		error("File could not be opened");
		return (0);
	}
	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (0);
	}
	if (!read_lines(fd, &map, game))
	{
		close(fd);
		return (0);
	}
	table->columns = ft_strlen(map[0]) - 1;
	table->map = map;
	close(fd);
	return (1);
}
