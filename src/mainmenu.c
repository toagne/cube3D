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
		//button->status = 0;
	}
	else if (button->status == 0)
	{
		button->colored->instances[0].enabled = true;
		button->white->instances[0].enabled = false;
		//button->status = 1;
	}
}

void	display_main_menu(t_table *table)
{
	if (table->bg_img->instances[0].z == 0)
	{
		mlx_set_instance_depth(&table->bg_img->instances[0], 9);
		mlx_set_instance_depth(&table->play_button.white->instances[0], 10);
		mlx_set_instance_depth(&table->play_button.colored->instances[0], 11);
		mlx_set_instance_depth(&table->exit_button.white->instances[0], 10);
		mlx_set_instance_depth(&table->exit_button.colored->instances[0], 11);
	}
	table->bg_img->instances[0].enabled = true;
	table->play_button.white->instances[0].enabled = true;
	table->exit_button.white->instances[0].enabled = true;
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
}

void	undisplay_main_menu(t_table *table)
{
	table->bg_img->instances[0].enabled = false;
	table->play_button.colored->instances[0].enabled = false;
	table->exit_button.white->instances[0].enabled = false;
	table->play_button.white->instances[0].enabled = false;
	table->exit_button.colored->instances[0].enabled = false;
}

void init_main_menu(t_table *table)
{
	mlx_image_t *img;
	t_button	play;
	t_button	exit;

	table->main_menu_on = 1;
	play.status = 1;
	exit.status = 1;
	img = load_image(table->mlx_start, "pngs/Background_0.png");
	mlx_resize_image(img, table->width, table->height);
	mlx_image_to_window(table->mlx_start, img, 0, 0);
	play.colored = load_image(table->mlx_start, "pngs/Play col_Button.png");
	mlx_resize_image(play.colored, table->width / 6, table->height / 6);
	mlx_image_to_window(table->mlx_start, play.colored, table->width / 2 - table->width / 6 / 2, table->height / 4);
	play.white = load_image(table->mlx_start, "pngs/Play Button.png");
	mlx_resize_image(play.white, table->width / 6, table->height / 6);
	mlx_image_to_window(table->mlx_start, play.white, table->width / 2 - table->width / 6 / 2, table->height / 4);
	exit.colored = load_image(table->mlx_start, "pngs/Exit  col_Button.png");
	mlx_resize_image(exit.colored, table->width / 6, table->height / 6);
	mlx_image_to_window(table->mlx_start, exit.colored, table->width / 2 - table->width / 6 / 2, table->height / 2);
	exit.white = load_image(table->mlx_start, "pngs/Exit Button.png");
	mlx_resize_image(exit.white, table->width / 6, table->height / 6);
	mlx_image_to_window(table->mlx_start, exit.white, table->width / 2 - table->width / 6 / 2, table->height / 2);
	mlx_put_string(table->mlx_start, "Our Cube Game", table->width / 2, 0);
	table->play_button = play;
	table->exit_button = exit;
	table->bg_img = img;
}