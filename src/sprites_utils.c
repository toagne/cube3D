/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:36 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/13 12:01:38 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_limits(t_table *table, t_enemy *sp, float v_offset)
{
	if (sp->x_start < 0)
	{
		sp->tx_start_x = -sp->x_start * (table->sprite_tx.width / 11)
			/ sp->screen_size;
		sp->x_start = 0;
	}
	if (sp->x_end >= table->width)
		sp->x_end = table->width - 1;
	if (sp->y_start < 0)
	{
		v_offset = -sp->y_start;
		sp->y_start = 0;
	}
	if (sp->y_end >= table->height)
		sp->y_end = table->height - 1;
	if (v_offset > 0)
		sp->tx_start_y = v_offset * (table->sprite_tx.height - 1)
			/ sp->screen_size;
	else
		sp->tx_start_y = 0;
}

void	convert_sprite_sizes(t_table *table, float angle_diff, t_enemy *sp)
{
	float	sprite_center_screen;
	float	v_offset;

	sprite_center_screen = (angle_diff + 30) * table->width / 60;
	sp->screen_size = T_SIZE * table->height / sp->dist;
	sp->x_start = sprite_center_screen - sp->screen_size / 2;
	sp->x_end = sprite_center_screen + sp->screen_size / 2;
	sp->y_start = table->height / 2 - sp->screen_size / 2;
	sp->y_end = table->height / 2 + sp->screen_size / 2;
	sp->tx_start_x = 0;
	v_offset = 0;
	check_limits(table, sp, v_offset);
}

void	order_sprites(t_enemy *sp)
{
	int		i;
	int		j;
	t_enemy	temp;

	i = -1;
	while (++i < N_ENEMIES - 1)
	{
		j = -1;
		while (++j < N_ENEMIES - i - 1)
		{
			if (sp[j].dist < sp[j + 1].dist)
			{
				temp = sp[j];
				sp[j] = sp[j + 1];
				sp[j + 1] = temp;
			}
		}
	}
}

void	set_treshold_for_movement(t_table *table, float *move_x,
	float *move_y, int i)
{
	float	threshold;
	float	speed;
	float	dx;
	float	dy;
	float	distance;

	threshold = 0.1f;
	speed = 10 + (i * 2);
	dx = table->player_x - table->enemies[i].x;
	dy = table->player_y - table->enemies[i].y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > threshold)
	{
		*move_x = (dx / distance) * table->d_t_in_s * speed;
		*move_y = (dy / distance) * table->d_t_in_s * speed;
	}
}

void	check_collisions(t_table *table, t_enemy *sp, t_collision *s_coll)
{
	if (s_coll->x1 != sp->x && s_coll->y1 != sp->y)
		s_coll->r = 15 * sqrt(2);
	else
		s_coll->r = 15;
	if (!wall_coll_w_circular_bumper(table, s_coll->x1, s_coll->y1, s_coll))
	{
		sp->x = s_coll->x1;
		sp->y = s_coll->y1;
	}
	else
	{
		if (!wall_coll_w_circular_bumper(table, sp->x, s_coll->y1, s_coll))
			sp->y = s_coll->y1;
		else if (!wall_coll_w_circular_bumper(table, s_coll->x1, sp->y, s_coll))
			sp->x = s_coll->x1;
	}
}
