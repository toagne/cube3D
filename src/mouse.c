/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:53 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/13 11:53:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_visual_with_mouse(t_table *table)
{
	int	delta_x_mouse;

	mlx_set_cursor_mode(table->mlx_start, MLX_MOUSE_HIDDEN);
	delta_x_mouse = table->x_mouse - table->mouse_last_x;
	if (delta_x_mouse != 0)
	{
		table->player_angle += delta_x_mouse * 0.5;
		if (table->player_angle < 0)
			table->player_angle += 360;
		if (table->player_angle >= 360)
			table->player_angle -= 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90)
				/ 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90)
				/ 180 * PI);
		mlx_set_mouse_pos(table->mlx_start, table->width / 2,
			table->height / 2);
		table->mouse_last_x = table->width / 2;
		table->mouse_last_y = table->height / 2;
	}
}

static int	click_play_button(t_table *t)
{
	if (t->x_mouse > t->play_button.white->instances[0].x
		&& t->x_mouse < t->play_button.white->instances[0].x + t->width / 6
		&& t->y_mouse > t->play_button.white->instances[0].y
		&& t->y_mouse < t->play_button.white->instances[0].y + t->height / 6)
	{
		t->play_button.status = 0;
		animate_button(&t->play_button);
		if (mlx_is_mouse_down(t->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{	
			t->main_menu_on = 0;
			undisplay_main_menu(t);
			return (1);
		}
	}
	else
	{
		t->play_button.status = 1;
		animate_button(&t->play_button);
	}
	return (0);
}

static void	click_exit_button(t_table *t)
{
	if (t->x_mouse > t->exit_button.white->instances[0].x
		&& t->x_mouse < t->exit_button.white->instances[0].x + t->width / 6
		&& t->y_mouse > t->exit_button.white->instances[0].y
		&& t->y_mouse < t->exit_button.white->instances[0].y + t->height / 6)
	{
		t->exit_button.status = 0;
		animate_button(&t->exit_button);
		if (mlx_is_mouse_down(t->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{
			free_all(t);
			exit (EXIT_SUCCESS);
		}
	}
	else
	{
		t->exit_button.status = 1;
		animate_button(&t->exit_button);
	}
}

static void	click_controls_button(t_table *t)
{
	if (t->x_mouse > t->controls_button.white->instances[0].x
		&& t->x_mouse < t->controls_button.white->instances[0].x + t->width / 6
		&& t->y_mouse > t->controls_button.white->instances[0].y && t->y_mouse
		< t->controls_button.white->instances[0].y + t->height / 6)
	{
		t->controls_button.status = 0;
		animate_button(&t->controls_button);
		if (mlx_is_mouse_down(t->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{
			display_controls(t);
			undisplay_main_menu(t);
		}
	}
	else
	{
		t->controls_button.status = 1;
		animate_button(&t->controls_button);
	}
}

void	ft_mouse(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	mlx_get_mouse_pos(table->mlx_start, &table->x_mouse, &table->y_mouse);
	if (table->controls_on)
		return ;
	if (table->main_menu_on == 0)
	{
		move_visual_with_mouse(table);
		return ;
	}
	if (click_play_button(table))
		return ;
	click_controls_button(table);
	click_exit_button(table);
}
