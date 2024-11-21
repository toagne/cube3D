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

static int	check_empty_file(int fd, char **line, char **map)
{
	*line = get_next_line(fd);
	if (!(*line))
	{
		free(map);
		return (0);
	}
	return (1);
}

/* static	int count_chars(char *line, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] != c)
			count++;
		i++;
	}
	return (count);
} */

/* static char	*remove_spaces(char *line)
{
	char	*newstr;
	int		j;
	int		i;
	int		nspaces;

	i = 0;
	j = 0;
	nspaces = count_chars(line, ' ');
	if (!line)
		return (NULL);
	if (nspaces != 0)
	{
		newstr = ft_calloc((ft_strlen(line) - nspaces) + 1, sizeof(char));
		if (!newstr)
			return (NULL);
		while (line[j])
		{
			if (line[j] != ' ')
			{
				newstr[i] = line[j];
				++i;
			}
			++j;
		}
		newstr[i] = '\0';
		return (newstr);
	}
	return (line);
} */

/* static char *remove_spaces_and_nl(char *line)
{
	char	*trimmed;
	char	*newstr;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (NULL);
	newstr = remove_spaces(trimmed);
	free(trimmed);
	if (!newstr)
		return (NULL);
	return (newstr);
} */

static int	read_lines(int fd, char ***map, t_table *table)
{
	char	*line;
	int		ln;
	char	*trimmed;

	line = NULL;
	if (!check_empty_file(fd, &line, *map))
		return (0);
	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
	{
		free(*map);
		return (0);
	}
	(*map)[0] = trimmed;
	ln = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		*map = ft_realloc(*map, ln * sizeof(char *), (ln + 1) * sizeof(char *));
		if (line)
			trimmed = ft_strtrim(line, " \n");
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
	//printf("%d x %d\n", table->player_col, table->player_row);
	table->player_x = (float)table->player_col * T_SIZE + T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE + T_SIZE / 2;
	//printf("%f x %f\n", table->player_x, table->player_y);
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
		newline[src_len] = ' ';
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

int	read_map(t_table *table, int fd)
{
	char	**map;

	map = malloc(1 * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (1);
	}
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
	//printf("table->columns = %zu\n", table->columns);
	table->map = map;
	set_player_position(table);
	return (0);
}
