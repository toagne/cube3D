/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:14:14 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/29 13:21:56 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_dot(t_table *table, int value_x, int value_y, int range)
{
	int	x;
	int	y;

	y = value_y - range;
	while (y++ < value_y + range)
	{
		x = value_x - range;
		while (x++ < value_x + range)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
	}
}