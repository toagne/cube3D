/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_state_images.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:42:10 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 14:11:13 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_controls(t_table *table)
{
	table->controlsimg = load_image(table->mlx_start,
			"pngs/controlsbackground.png");
	if (!table->controlsimg)
	{
		printf("init control image faied \n");
		return (1);
	}
	if (mlx_image_to_window(table->mlx_start, table->controlsimg, 0, 0) == -1)
	{
		printf("init control image faied \n");
		return (1);
	}
	if (!mlx_resize_image(table->controlsimg, table->width, table->height))
	{
		printf("init control image faied \n");
		return (1);
	}
	table->controlsimg->instances[0].enabled = false;
	return (0);
}

int	init_gamewon(t_table *table)
{
	table->gamewonimg = load_image(table->mlx_start, "pngs/gamewon.png");
	if (!table->gamewonimg)
	{
		printf("init gamewon image faied \n");
		return (1);
	}
	if (mlx_image_to_window(table->mlx_start, table->gamewonimg, 0, 0) == -1)
	{
		printf("init gamewon image faied \n");
		return (1);
	}
	if (!mlx_resize_image(table->gamewonimg, table->width, table->height))
	{
		printf("init gamewon image faied \n");
		return (1);
	}
	table->gamewonimg->instances[0].enabled = false;
	return (0);
}

int	init_gameover(t_table *table)
{
	table->gameoverimg = load_image(table->mlx_start, "pngs/gameover.png");
	if (!table->gameoverimg)
	{
		printf("init gameover image faied \n");
		return (1);
	}
	if (mlx_image_to_window(table->mlx_start, table->gameoverimg, 0, 0) == -1)
	{
		printf("init gameover image faied \n");
		return (1);
	}
	if (!mlx_resize_image(table->gameoverimg, table->width, table->height))
	{
		printf("init gameover image faied \n");
		return (1);
	}
	table->gameoverimg->instances[0].enabled = false;
	return (0);
}
