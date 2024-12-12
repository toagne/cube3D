/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_state_images.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:42:10 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:14:40 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

void	init_controls(t_table *table)
{
	table->controlsimg = load_image(table->mlx_start,
			"pngs/controlsbackground.png");
	mlx_image_to_window(table->mlx_start, table->controlsimg, 0, 0);
	mlx_resize_image(table->controlsimg, table->width, table->height);
	table->controlsimg->instances[0].enabled = false;
}

void	init_gamewon(t_table *table)
{
	table->gamewonimg = load_image(table->mlx_start, "pngs/gamewon.png");
	mlx_image_to_window(table->mlx_start, table->gamewonimg, 0, 0);
	mlx_resize_image(table->gamewonimg, table->width, table->height);
	table->gamewonimg->instances[0].enabled = false;
}

void	init_gameover(t_table *table)
{
	table->gameoverimg = load_image(table->mlx_start, "pngs/gameover.png");
	mlx_image_to_window(table->mlx_start, table->gameoverimg, 0, 0);
	mlx_resize_image(table->gameoverimg, table->width, table->height);
	table->gameoverimg->instances[0].enabled = false;
}
