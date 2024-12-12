/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:50:20 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:00:53 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*ft_skipwhitespace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == '\n')
		++str;
	return (str);
}

static int	prepare_line(char *line, char **trimnl)
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

static int	process_trimmed_line(char *line, char *trimnl, t_table *table)
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
	int	result;

	result = prepare_line(line, trimnl);
	if (result != 3)
		return (result);
	return (process_trimmed_line(line, *trimnl, table));
}
