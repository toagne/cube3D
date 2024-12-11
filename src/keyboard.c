/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 15:06:00 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_visual(t_table *t)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_LEFT))
	{
		t->player_angle -= t->d_t_in_s * 150;
		if (t->player_angle < 0)
			t->player_angle += 360;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_RIGHT))
	{
		t->player_angle += t->d_t_in_s * 150;
		if (t->player_angle > 359)
			t->player_angle -= 360;
	}
	t->player_delta_x = cos((float)t->player_angle / 180 * PI);
	t->player_delta_y = sin((float)t->player_angle / 180 * PI);
	t->player_delta_x_ad = cos((float)(t->player_angle + 90) / 180 * PI);
	t->player_delta_y_ad = sin((float)(t->player_angle + 90) / 180 * PI);
}

void	move_up_down(t_table *t, t_collision *p_coll)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_W))
	{
		p_coll->x1 = t->player_x + t->player_delta_x * t->d_t_in_s * 150;
		p_coll->y1 = t->player_y + t->player_delta_y * t->d_t_in_s * 150;
		if (!wall_coll_w_circular_bumper(t, p_coll->x1, t->player_y, p_coll))
			t->player_x = p_coll->x1;
		if (!wall_coll_w_circular_bumper(t, t->player_x, p_coll->y1, p_coll))
			t->player_y = p_coll->y1;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_S))
	{
		p_coll->x1 = t->player_x - t->player_delta_x * t->d_t_in_s * 150;
		p_coll->y1 = t->player_y - t->player_delta_y * t->d_t_in_s * 150;
		if (!wall_coll_w_circular_bumper(t, p_coll->x1, t->player_y, p_coll))
			t->player_x = p_coll->x1;
		if (!wall_coll_w_circular_bumper(t, t->player_x, p_coll->y1, p_coll))
			t->player_y = p_coll->y1;
	}
}

void	move_right_left(t_table *t, t_collision *p_coll)
{
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_D))
	{
		p_coll->x1 = t->player_x + t->player_delta_x_ad * t->d_t_in_s * 150;
		p_coll->y1 = t->player_y + t->player_delta_y_ad * t->d_t_in_s * 150;
		if (!wall_coll_w_circular_bumper(t, p_coll->x1, t->player_y, p_coll))
			t->player_x = p_coll->x1;
		if (!wall_coll_w_circular_bumper(t, t->player_x, p_coll->y1, p_coll))
			t->player_y = p_coll->y1;
	}
	if (mlx_is_key_down(t->mlx_start, MLX_KEY_A))
	{
		p_coll->x1 = t->player_x - t->player_delta_x_ad * t->d_t_in_s * 150;
		p_coll->y1 = t->player_y - t->player_delta_y_ad * t->d_t_in_s * 150;
		if (!wall_coll_w_circular_bumper(t, p_coll->x1, t->player_y, p_coll))
			t->player_x = p_coll->x1;
		if (!wall_coll_w_circular_bumper(t, t->player_x, p_coll->y1, p_coll))
			t->player_y = p_coll->y1;
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
