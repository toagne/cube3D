/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:36:58 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 11:50:51 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	init_b_img(t_table *table, t_button *b, char *c, char *w)
{
	b->colored = load_image(table->mlx_start, c, table);
	b->white = load_image(table->mlx_start, w, table);
	if (!b->colored || !b->white)
		return (1);
	if (!mlx_resize_image(b->colored, b->width, b->height))
		return (1);
	if (!mlx_resize_image(b->white, b->width, b->height))
		return (1);
	if (mlx_image_to_window(table->mlx_start, b->colored, b->x, b->y) == -1)
		return (1);
	if (mlx_image_to_window(table->mlx_start, b->white, b->x, b->y) == -1)
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
	int			button_x;

	play.status = 1;
	exit.status = 1;
	controls.status = 1;
	button_x = table->width / 2 - table->width / 6 / 2;
	set_button_height_width(&play, table->width / 6, table->height / 6);
	set_button_height_width(&exit, table->width / 6, table->height / 6);
	set_button_height_width(&controls, table->width / 6, table->height / 6);
	set_button_x_y(&play, button_x, table->height / 4);
	set_button_x_y(&exit, button_x, table->height / 2);
	set_button_x_y(&controls, button_x, table->height * 0.75);
	if (init_b_img(table, &play, "pngs/Play col.png", "pngs/Play.png"))
		return (1);
	if (init_b_img(table, &exit, "pngs/Exit col.png", "pngs/Exit.png"))
		return (1);
	if (init_b_img(table, &controls, "pngs/Cntrls col.png", "pngs/Cntrls.png"))
		return (1);
	table->controls_button = controls;
	table->play_button = play;
	table->exit_button = exit;
	return (0);
}
