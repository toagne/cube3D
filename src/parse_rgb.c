/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:39:51 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 08:51:43 by mpellegr         ###   ########.fr       */
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
		{
			table->duplicate_id = 1;
			free(array);
		}
	}
	else if (c == 'C')
	{
		if (!table->c_color)
			table->c_color = array;
		else
		{
			table->duplicate_id = 1;
			free(array);
		}
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

static int	check_rgb_len(char **rgb_arr, t_table *table)
{
	int	i;

	i = 0;
	while (rgb_arr[i])
		++i;
	if (i != 3)
	{
		free_table(&rgb_arr);
		ft_error("Invalid floor or ceiling color", table);
		return (1);
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
	if (check_rgb_len(rgb_arr, table))
		return (1);
	array = ft_calloc(3, sizeof(int));
	if (!array)
	{
		free_table(&rgb_arr);
		return (1);
	}
	if (convert_arr_to_int(array, rgb_arr))
	{
		free_table(&rgb_arr);
		free(array);
		return (1);
	}
	check_duplicate_color(table, array, c);
	free_table(&rgb_arr);
	return (0);
}
