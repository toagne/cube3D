/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 13:59:37 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_visual(t_table *t, int *render_flag)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_LEFT))
	{
		*render_flag = 1;
		t->player_angle -= t->d_t_in_s * 150;
		if (t->player_angle < 0)
			t->player_angle += 360;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_RIGHT))
	{
		*render_flag = 1;
		t->player_angle += t->d_t_in_s * 150;
		if (t->player_angle > 359)
			t->player_angle -= 360;
	}
	t->player_delta_x = cos((float)t->player_angle / 180 * PI);
	t->player_delta_y = sin((float)t->player_angle / 180 * PI);
	t->player_delta_x_ad = cos((float)(t->player_angle + 90) / 180 * PI);
	t->player_delta_y_ad = sin((float)(t->player_angle + 90) / 180 * PI);
}

void	move_up_down(t_table *t, float *new_x, float *new_y, int *render_flag)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_W))
	{
		*render_flag = 1;
		*new_x = t->player_x + t->player_delta_x * t->d_t_in_s * 150;
		*new_y = t->player_y + t->player_delta_y * t->d_t_in_s * 150;
		if (!wall_collision_w_circular_bumper(t, *new_x, t->player_y,
				t->player_x, t->player_y, 10))
			t->player_x = *new_x;
		if (!wall_collision_w_circular_bumper(t, t->player_x, *new_y,
				t->player_x, t->player_y, 10))
			t->player_y = *new_y;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_S))
	{
		*render_flag = 1;
		*new_x = t->player_x - t->player_delta_x * t->d_t_in_s * 150;
		*new_y = t->player_y - t->player_delta_y * t->d_t_in_s * 150;
		if (!wall_collision_w_circular_bumper(t, *new_x, t->player_y,
				t->player_x, t->player_y, 10))
			t->player_x = *new_x;
		if (!wall_collision_w_circular_bumper(t, t->player_x, *new_y,
				t->player_x, t->player_y, 10))
			t->player_y = *new_y;
	}
}

void	move_right_left(t_table *t, float *new_x, float *new_y, int *rend_flag)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_D))
	{
		*rend_flag = 1;
		*new_x = t->player_x + t->player_delta_x_ad * t->d_t_in_s * 150;
		*new_y = t->player_y + t->player_delta_y_ad * t->d_t_in_s * 150;
		if (!wall_collision_w_circular_bumper(t, *new_x, t->player_y,
				t->player_x, t->player_y, 10))
			t->player_x = *new_x;
		if (!wall_collision_w_circular_bumper(t, t->player_x, *new_y,
				t->player_x, t->player_y, 10))
			t->player_y = *new_y;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_A))
	{
		*rend_flag = 1;
		*new_x = t->player_x - t->player_delta_x_ad * t->d_t_in_s * 150;
		*new_y = t->player_y - t->player_delta_y_ad * t->d_t_in_s * 150;
		if (!wall_collision_w_circular_bumper(t, *new_x, t->player_y,
				t->player_x, t->player_y, 10))
			t->player_x = *new_x;
		if (!wall_collision_w_circular_bumper(t, t->player_x, *new_y,
				t->player_x, t->player_y, 10))
			t->player_y = *new_y;
	}
}

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_table	*table;

	table = (t_table *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(table->mlx_start);
		exit (EXIT_SUCCESS);
	}
	if (table->main_menu_on)
		return ;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		table->is_attacking = 1;
		table->kill = 1;
	}
}
