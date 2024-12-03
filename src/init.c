/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/03 12:14:11 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_table *table)
{
	ft_memset(table, 0, sizeof(t_table));
	get_monitor_size(&table->width, &table->height);
	table->player_angle = 270; // to ghange according NSEW where the player is looking on the map
	table->player_delta_x = cos((float)table->player_angle / 180 * PI);
	table->player_delta_y = sin((float)table->player_angle / 180 * PI);
	table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
	table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	table->sprite_x = 100;
	table->sprite_y = 100;
	table->x_aligned_flag = 0;
	table->y_aligned_flag = 0;
	table->y_stuck = 0;
	table->e_spawn_pos_x = 0;
	table->e_spawn_pos_y = 0;
	table->lcg_seed = get_time('a');
	table->n_of_rays = table->width / 2;
	table->last_time = get_time('b');
	table->w_colors = (uint32_t **)ft_calloc((table->height), sizeof(uint32_t *));
	if (!table->w_colors) {
		printf("Memory allocation failed for rows\n");
		return;
	}
	int i = -1;
	while (++i < table->height)
	{
		table->w_colors[i] = (uint32_t *)ft_calloc((table->width), sizeof(uint32_t));
		if (!table->w_colors[i])
		{
			printf("Memory allocation failed for rows\n");
			return ;
		}
	}
}
