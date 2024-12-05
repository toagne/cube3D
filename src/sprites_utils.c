/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:36 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/05 17:20:53 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	real_check(float p_fov_r, float p_fov_l, float s_r_angle,
	float s_l_angle)
{
	int	visible;

	visible = 0;
	if (p_fov_r < p_fov_l)
	{
		// FOV does not wrap around 0 degrees
		visible = (s_l_angle >= p_fov_r && s_l_angle <= p_fov_l)
			|| (s_r_angle >= p_fov_r && s_r_angle <= p_fov_l)
			|| (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}
	else
	{
		// FOV wraps around 0 degrees
		visible = (s_l_angle >= p_fov_r || s_l_angle <= p_fov_l)
			|| (s_r_angle >= p_fov_r || s_r_angle <= p_fov_l)
			|| (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}
	return (visible);
}

int	check_sprite_is_visible(t_table *table, t_enemy sp)
{
	float	half_width_angle;
	float	s_l_angle;
	float	s_r_angle;
	float	p_fov_r;
	float	p_fov_l;

	half_width_angle = atan2(table->sprite_tx.width / 11 / 2, sp.dist) * 180 / PI;
	s_l_angle = sp.angle - half_width_angle;
	s_r_angle = sp.angle + half_width_angle;
	if (s_l_angle < 0)
		s_l_angle += 360;
	if (s_r_angle >= 360)
		s_r_angle -= 360;
	p_fov_r = table->player_angle - 30;
	p_fov_l = table->player_angle + 30;
	if (p_fov_r < 0)
		p_fov_r += 360;
	if (p_fov_l >= 360)
		p_fov_l -= 360;
	if (real_check(p_fov_r, p_fov_l, s_r_angle, s_l_angle))
		return (1);
	return (0);
}

void	convert_sprite_sizes(t_table *table, float angle_diff, t_enemy *sp)
{
	float	sprite_center_screen;

	sprite_center_screen = (angle_diff + 30) * table->width / 60;
	sp->screen_size = T_SIZE * table->height / sp->dist;
	sp->x_start = sprite_center_screen - sp->screen_size / 2;
	sp->x_end = sprite_center_screen + sp->screen_size / 2;
	sp->y_start = table->height / 2 - sp->screen_size / 2;
	sp->y_end = table->height / 2 + sp->screen_size / 2;
	sp->tx_start_x = 0;
	if (sp->x_start < 0)
	{
		sp->tx_start_x = -sp->x_start * (table->sprite_tx.width / 11) / sp->screen_size;
		sp->x_start = 0;
	}
	if (sp->x_end >= table->width)
		sp->x_end = table->width - 1;
	if (sp->y_start < 0)
		sp->y_start = 0;
	if (sp->y_end >= table->height)
		sp->y_end = table->height - 1;
}
