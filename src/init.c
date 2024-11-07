/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/07 18:11:17 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_table *table)
{
    table->width = 2048 / 2;
    table->height = 1024 / 2;
    table->player_angle = M_PI / 2;
    table->player_delta_x = cos(table->player_angle) * 30;
	table->player_delta_y = sin(table->player_angle) * 30;
}