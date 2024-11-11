/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/11 16:40:06 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_table *table)
{
	table->width = 2048;
	table->height = 1024;
	table->player_angle = PI * 3 / 2; // to ghange according NSEW where the player is looking on the map
	table->player_delta_x = cos(table->player_angle) * 20;
	table->player_delta_y = sin(table->player_angle) * 20;
}