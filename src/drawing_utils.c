/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:14:14 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 13:04:42 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int find_increment(int i0, int i1)
{
	int i;

	if (i0 < i1)
		i = 1;
	else
		i = -1;
	return (i);
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color, t_table *table, int type)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	sx = find_increment(x0, x1);
	sy = find_increment(y0, y1);
	while (1)
	{
		if (type == 1)
		{
			if (color != table->w_colors[y0][x0])
				table->w_colors[y0][x0] = color;
		}
		else
			mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;// Stop if we’ve reached the end point
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

/* void	draw_dot(t_table *table, int value_x, int value_y, int range)
{
	int	x;
	int	y;

	y = value_y - range;
	while (y++ < value_y + range)
	{
		x = value_x - range;
		while (x++ < value_x + range)
			mlx_put_pixel(table->mlx_minimap, x, y, 0xFF0000FF);
	}
} */

/* void	draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color)
{
	const double step = 0.01;
	double angle;
	int x;
	int y;

	angle = 0;
	while (angle <= 2 * PI)
	{
		x = x_center + (int)(radius * cos(angle));
		y = y_center + (int)(radius * sin(angle));
		mlx_put_pixel(image, x, y, color);
		angle += step;
	}
} */
// draw circle should not be used