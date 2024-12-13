/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:14:14 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/13 11:42:44 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_increment(int i0, int i1)
{
	int	i;

	if (i0 < i1)
		i = 1;
	else
		i = -1;
	return (i);
}

static void	find_next_point(t_line *line)
{
	line->e2 = 2 * line->err;
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
}

void	draw_line(t_line *line, t_table *table, int type, mlx_image_t *img)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->err = line->dx - line->dy;
	line->sx = find_increment(line->x0, line->x1);
	line->sy = find_increment(line->y0, line->y1);
	while (1)
	{
		if (type == 1)
		{
			if (line->color != table->w_colors[line->y0][line->x0])
				table->w_colors[line->y0][line->x0] = line->color;
		}
		else
			mlx_put_pixel(img, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		find_next_point(line);
	}
}
