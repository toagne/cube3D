/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/14 10:51:56 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_table *table)
{
	ft_memset(table, 0, sizeof(t_table));
	table->width = 2048;
	table->height = 1024;
	table->player_angle = 270; // to ghange according NSEW where the player is looking on the map
	table->player_delta_x = cos((float)table->player_angle / 180 * PI) * 20;
	table->player_delta_y = sin((float)table->player_angle / 180 * PI) * 20;
}
