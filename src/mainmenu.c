/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:50:38 by omartela          #+#    #+#             */
/*   Updated: 2024/12/04 13:55:46 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void animate_button(t_button *button)
{
	if (button->status == 1)
	{
		button->white->instances[0].enabled = true;
		button->colored->instances[0].enabled = false;
	}
	else if (button->status == 0)
	{
		button->colored->instances[0].enabled = true;
		button->white->instances[0].enabled = false;
	}
}

void	display_main_menu(t_table *table)
{
	mlx_set_cursor_mode(table->mlx_start, MLX_MOUSE_NORMAL);
	mlx_set_instance_depth(&table->bg_img->instances[0], 13);
	mlx_set_instance_depth(&table->play_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->play_button.colored->instances[0], 15);
	mlx_set_instance_depth(&table->exit_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->exit_button.colored->instances[0], 15);
	mlx_set_instance_depth(&table->controls_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->controls_button.colored->instances[0], 15);
	table->bg_img->instances[0].enabled = true;
	table->play_button.white->instances[0].enabled = true;
	table->exit_button.white->instances[0].enabled = true;
	table->controls_button.white->instances[0].enabled = true;
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
}

void	undisplay_main_menu(t_table *table)
{
	table->bg_img->instances[0].enabled = false;
	table->play_button.colored->instances[0].enabled = false;
	table->play_button.white->instances[0].enabled = false;
	table->exit_button.white->instances[0].enabled = false;
	table->exit_button.colored->instances[0].enabled = false;
	table->controls_button.white->instances[0].enabled = false;
	table->controls_button.colored->instances[0].enabled = false;
}

static mlx_image_t *init_background(t_table *table)
{
    mlx_image_t *img;
    
    img = load_image(table->mlx_start, "pngs/Background_0.png");
	if (!img)
		return (NULL);
    if (!mlx_resize_image(img, table->width, table->height))
		return (NULL);
    if (mlx_image_to_window(table->mlx_start, img, 0, 0) == -1)
		return (NULL);
    return (img);
}

int	init_button_img(t_table *table, t_button *button, char *cpath, char *wpath)
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

void	set_button_height_width(t_button *button, int w, int h)
{
	button->height = h;
	button->width = w;
}

void	set_button_x_y(t_button *button, int x, int y)
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

int init_main_menu(t_table *table)
{
	table->main_menu_on = 1;
	table->bg_img = init_background(table);
	if (!table->bg_img)
		return (1);
	if (init_buttons(table))
		return (1);
	return (0);
}

