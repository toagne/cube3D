/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:41:29 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 17:14:23 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

void	get_monitor_size(int *width, int *height)
{
	mlx_t	*temp;
	int32_t w;
	int32_t h;

	temp = mlx_init(1, 1, "", false);
	if (!temp)
	{
		;//error
	}
	mlx_get_monitor_size(0, &w, &h);
	mlx_terminate(temp);
	*width = w / 1.5;
	*height = h / 1.5;
}

float	deg_to_rad(float deg)
{
	return ((float)deg / 180 * PI);
}

void	draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color)
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
}
//should not be used