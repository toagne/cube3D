/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:36:58 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 09:37:01 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	init_button_img(t_table *table, t_button *button, char *cpath, char *wpath)
{
	button->colored = load_image(table->mlx_start, cpath);
	button->white = load_image(table->mlx_start, wpath);
	if (!button->colored || !button->white)
		return (1);
	if (!mlx_resize_image(button->colored, button->width, button->height))
		return (1);
	if (!mlx_resize_image(button->white, button->width, button->height))
		return (1);
	if (mlx_image_to_window(table->mlx_start, button->colored, button->x, button->y) == -1)
		return (1);
	if (mlx_image_to_window(table->mlx_start, button->white, button->x, button->y) == -1)
		return (1);
	return (0);
}

static void	set_button_height_width(t_button *button, int w, int h)
{
	button->height = h;
	button->width = w;
}

static void	set_button_x_y(t_button *button, int x, int y)
{
	button->x = x;
	button->y = y;
}
int	init_buttons(t_table *table)
{
	t_button	play;
	t_button	exit;
	t_button	controls;

	play.status = 1;
	exit.status = 1;
	controls.status = 1;
	set_button_height_width(&play, table->width / 6, table->height / 6);
	set_button_height_width(&exit, table->width / 6, table->height / 6);
	set_button_height_width(&controls, table->width / 6, table->height / 6);
	set_button_x_y(&play, table->width / 2 - table->width / 6 / 2, table->height / 4);
	set_button_x_y(&exit, table->width / 2 - table->width / 6 / 2, table->height / 2);
	set_button_x_y(&controls, table->width / 2 - table->width / 6 / 2, table->height * 0.75);
	if (init_button_img(table, &play, "pngs/Play col_Button.png", "pngs/Play Button.png"))
		return (1);
	if (init_button_img(table, &exit, "pngs/Exit  col_Button.png", "pngs/Exit Button.png"))
		return (1);
	if (init_button_img(table, &controls, "pngs/Controls  col_Button.png", "pngs/Controls Button.png"))
		return (1);
	table->controls_button = controls;
	table->play_button = play;
	table->exit_button = exit;
	return (0);
}