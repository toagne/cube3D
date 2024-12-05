/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/05 17:21:59 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_static_data(t_table *table)
{
	int i;

	ft_memset(table, 0, sizeof(t_table));
	get_monitor_size(&table->width, &table->height);
	table->player_delta_x = cos((float)table->player_angle / 180 * PI);
	table->player_delta_y = sin((float)table->player_angle / 180 * PI);
	table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
	table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	table->lcg_seed = get_time('a');
	table->n_of_rays = table->width / 2;
	table->last_time = get_time('b');
	table->w_colors = (uint32_t **)ft_calloc((table->height), sizeof(uint32_t *));
	if (!table->w_colors) {
		printf("Memory allocation failed for rows\n");
		return;
	}
	i = -1;
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

void	init_dynamic_data(t_table *table)
{
	if (table->player_dir == 'N')
		table->player_angle = 270;
	else if (table->player_dir == 'S')
		table->player_angle = 90;
	else if (table->player_dir == 'E')
		table->player_angle = 180;
	else if (table->player_dir == 'W')
		table->player_angle = 0;
	init_enemies(table);
	table->mouse_last_x = table->width / 2;
	table->mouse_last_y = table->height / 2;
	mlx_set_mouse_pos(table->mlx_start, table->width / 2, table->height / 2);
	table->kill = 0;
	table->sprite_frames = 0;
}
