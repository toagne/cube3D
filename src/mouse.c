/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:53 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 13:18:37 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_visual_with_mouse(t_table *table)
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
		// draw_minimap(table);
		// draw_raycasting(table);
	}
}

void	ft_mouse(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	mlx_get_mouse_pos(table->mlx_start, &table->x_mouse, &table->y_mouse);
	if (table->main_menu_on == 0)
	{
		move_visual_with_mouse(table);
		return ;
	}
	if (table->x_mouse > table->play_button.white->instances[0].x && table->x_mouse < table->play_button.white->instances[0].x + table->width / 6 \
	&& table->y_mouse > table->play_button.white->instances[0].y && table->y_mouse < table->play_button.white->instances[0].y + table->height / 6)
	{
		table->play_button.status = 0;
		animate_button(&table->play_button);
		if (mlx_is_mouse_down(table->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{	
			table->main_menu_on = 0;
			undisplay_main_menu(table);
			return ;
		}
	}
	else
	{
		table->play_button.status = 1;
		animate_button(&table->play_button);
	}
	if (table->x_mouse > table->exit_button.white->instances[0].x && table->x_mouse < table->exit_button.white->instances[0].x + table->width / 6 \
	&& table->y_mouse > table->exit_button.white->instances[0].y && table->y_mouse < table->exit_button.white->instances[0].y + table->height / 6)
	{
		table->exit_button.status = 0;
		animate_button(&table->exit_button);
		if (mlx_is_mouse_down(table->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{
			mlx_terminate(table->mlx_start);
			exit (EXIT_SUCCESS);
		}
	}
	else
	{
		table->exit_button.status = 1;
		animate_button(&table->exit_button);
	}
}
