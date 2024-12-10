/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:47:36 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 11:18:24 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	real_check(float p_fov_r, float p_fov_l, float s_r_angle,
	float s_l_angle)
{
	int	visible;

	visible = 0;
	if (p_fov_l < p_fov_r)
	{
		// FOV does not wrap around 0 degrees
		visible = (s_l_angle >= p_fov_l && s_l_angle <= p_fov_r)
			|| (s_r_angle >= p_fov_l && s_r_angle <= p_fov_r)
			|| (s_l_angle <= p_fov_l && s_r_angle >= p_fov_r)
			|| (s_l_angle <= p_fov_l && s_r_angle >= 0)
			|| (s_r_angle >= p_fov_r && s_l_angle <= 360);
	}
	else
	{
		// FOV wraps around 0 degrees
		visible = (s_l_angle >= p_fov_l || s_l_angle <= p_fov_r)
			|| (s_r_angle >= p_fov_l || s_r_angle <= p_fov_r)
			|| (s_l_angle <= p_fov_l && s_r_angle >= p_fov_r)
			|| (s_l_angle <= p_fov_l && s_r_angle >= 0)
			|| (s_r_angle >= p_fov_r && s_l_angle <= 360);
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

	half_width_angle = atan2((table->sprite_tx.width / 11)
			/ 2, sp.dist) * 180 / PI;
	s_l_angle = sp.angle - half_width_angle;
	s_r_angle = sp.angle + half_width_angle;
	if (s_l_angle < 0)
		s_l_angle += 360;
	if (s_r_angle >= 360)
		s_r_angle -= 360;
	// printf("s_a = %f\n", sp.angle);
	// printf("half s_a = %f\n", half_width_angle);
	// printf("s_l_a = %f	s_r_a = %f\n", s_l_angle, s_r_angle);
	p_fov_l = table->player_angle - 30;
	p_fov_r = table->player_angle + 30;
	if (p_fov_l < 0)
		p_fov_l += 360;
	if (p_fov_r >= 360)
		p_fov_r -= 360;
	// printf("p_a = %f\n", table->player_angle);
	// printf("p_fof_l = %f	p_fov_r = %f\n", p_fov_l, p_fov_r);
	if (real_check(p_fov_r, p_fov_l, s_r_angle, s_l_angle))
		return (1);
	return (0);
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
