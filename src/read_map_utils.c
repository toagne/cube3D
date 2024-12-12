/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:34:15 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:15:48 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	find_length_of_longest_line(char **map)
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

static char	*fill_ones(int len, char *line)
{
	char	*newline;
	int		src_len;
	int		i;

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
	i = 0;
	while (i < len)
	{
		if (newline[i] == ' ')
			newline[i] = '1';
		++i;
	}
	return (newline);
}

int	fill_ones_to_map(char ***map)
{
	size_t	i;
	size_t	len;
	char	*temp;

	i = 0;
	len = find_length_of_longest_line(*map);
	while ((*map)[i])
	{
		if (ft_strlen((*map)[i]) != len)
		{
			temp = fill_ones(len, (*map)[i]);
			if (!temp)
				return (1);
			free((*map)[i]);
			(*map)[i] = temp;
		}
		++i;
	}
	return (0);
}
