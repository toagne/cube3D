/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:39:51 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:28:37 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_duplicate_color(t_table *table, int *array, char c)
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

static int	convert_arr_to_int(int *array, char **rgb_arr)
{
	int	i;
	int	number;

	i = 0;
	while (rgb_arr[i])
	{
		number = ft_atoi(rgb_arr[i]);
		if ((rgb_arr[i][0] != '0' && number == 0) || number == -1)
		{
			free_table(&rgb_arr);
			free(array);
			return (1);
		}
		array[i] = number;
		++i;
	}
	return (0);
}

int	parse_rgb(t_table *table, char *color, char c)
{
	char	**rgb_arr;
	int		*array;

	rgb_arr = ft_split(color, ',');
	free(color);
	if (!rgb_arr)
		return (1);
	array = ft_calloc(3, sizeof(int));
	if (!array)
	{
		free_table(&rgb_arr);
		return (1);
	}
	if (convert_arr_to_int(array, rgb_arr))
		return (1);
	check_duplicate_color(table, array, c);
	free_table(&rgb_arr);
	return (0);
}
