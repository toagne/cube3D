/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:50:38 by omartela          #+#    #+#             */
/*   Updated: 2024/11/27 15:50:46 by omartela         ###   ########.fr       */
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

void main_menu(t_table *table)
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
	mlx_resize_image(play.colored, 300, 300);
	mlx_image_to_window(table->mlx_start, play.colored, table->width / 2, 300);
	play.white = load_image(table->mlx_start, "pngs/Play Button.png");
	mlx_resize_image(play.white, 300, 300);
	mlx_image_to_window(table->mlx_start, play.white, table->width / 2, 300);
	exit.colored = load_image(table->mlx_start, "pngs/Exit Button.png");
	mlx_resize_image(exit.colored, 300, 300);
	mlx_image_to_window(table->mlx_start, exit.colored, table->width / 2, 650);
	exit.white = load_image(table->mlx_start, "pngs/Exit Button.png");
	mlx_resize_image(exit.white, 300, 300);
	mlx_image_to_window(table->mlx_start, exit.white, table->width / 2, 650);
	mlx_put_string(table->mlx_start, "Our Cube Game", table->width / 2, 0);
	table->play_button = play;
	table->exit_button = exit;
}