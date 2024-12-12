/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_identifier.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:43:16 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:30:09 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_ele_texture(char **texture_path, char *texture, int *dup_id)
{
	if (!(*texture_path))
		*texture_path = texture;
	else
		*dup_id = 1;
}

static void	choose_element_and_set(t_table *table, char *str, char *texture)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		set_ele_texture(&table->no_path_texture, texture, &table->duplicate_id);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		set_ele_texture(&table->so_path_texture, texture, &table->duplicate_id);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		set_ele_texture(&table->ws_path_texture, texture, &table->duplicate_id);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		set_ele_texture(&table->es_path_texture, texture, &table->duplicate_id);
}

static int	check_element_id(t_table *table, char *line, char *str)
{
	char	*temp;
	char	*temp1;

	if (ft_strncmp(line, str, 3) == 0)
	{
		temp = ft_strtrim(line, str);
		if (!temp)
			return (1);
		temp1 = ft_strtrim(temp, " ");
		free(temp);
		choose_element_and_set(table, str, temp1);
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
