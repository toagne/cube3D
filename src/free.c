/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:30:55 by omartela          #+#    #+#             */
/*   Updated: 2024/12/11 16:39:12 by mpellegr         ###   ########.fr       */
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

void	free_table(char ***table)
{
	int	i;

	i = 0;
	while ((*table)[i])
	{
		free((*table)[i]);
		++i;
	}
	free((*table));
	table = NULL;
}
