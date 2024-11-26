/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/26 17:30:09 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_table *table)
{
	ft_memset(table, 0, sizeof(t_table));
	table->width = 2048;
	table->height = 1024;
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
}
