/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:30:55 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 16:11:01 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(char ***map, size_t i)
{
	if ((*map) == NULL)
		return ;
	while (i > 0)
	{
		i--;
		free((*map)[i]);
	}
	free(*map);
	*map = NULL;
}

void	free_table(char ***table)
{
	int	i;

	i = 0;
	if ((*table) == NULL)
		return ;
	while ((*table)[i])
	{
		free((*table)[i]);
		++i;
	}
	free((*table));
	*table = NULL;
}

void	free_int_table(uint32_t ***table)
{
	int	i;

	i = 0;
	if (*table == NULL)
		return ;
	while ((*table)[i])
	{
		free((*table)[i]);
		(*table)[i] = NULL;
		++i;
	}
	free(*table);
	*table = NULL;
}

void	free_and_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_all(t_table *table)
{
	free_table(&table->map);
	free_int_table(&table->w_colors);
	free_int_table(&table->ball_texture.colors);
	free_int_table(&table->door_texture.colors);
	free_int_table(&table->win_texture.colors);
	free_int_table(&table->no_texture.colors);
	free_int_table(&table->so_texture.colors);
	free_int_table(&table->es_texture.colors);
	free_int_table(&table->ws_texture.colors);
	free_int_table(&table->sprite_tx.colors);
	free(table->c_color);
	free(table->f_color);
	table->c_color = NULL;
	table->f_color = NULL;
	free_and_null(&table->no_path_texture);
	free_and_null(&table->so_path_texture);
	free_and_null(&table->ws_path_texture);
	free_and_null(&table->es_path_texture);
}
