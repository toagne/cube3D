/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state_images.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:01:20 by omartela          #+#    #+#             */
/*   Updated: 2024/12/05 15:01:22 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

void	display_controls(t_table *table)
{
	table->menudelaytime = get_time('a');
	mlx_set_instance_depth(&table->controlsimg->instances[0], 16);
	table->controlsimg->instances[0].enabled = true;
	table->controls_on = 1;
}

void	init_controls(t_table *table)
{
	table->controlsimg = load_image(table->mlx_start, "pngs/controlsbackground.png");
	mlx_image_to_window(table->mlx_start, table->controlsimg, 0, 0);
	mlx_resize_image(table->controlsimg, table->width, table->height);
	table->controlsimg->instances[0].enabled = false;
}

void	display_gamewon(t_table *table)
{
	table->menudelaytime = get_time('a');
	table->gamewonimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gamewonimg->instances[0], 16);
	table->gamewon_on = 1;
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

void	display_gameover(t_table *table)
{
	table->menudelaytime = get_time('a');
	table->gameoverimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gameoverimg->instances[0], 16);
	table->gameover_on = 1;
}

void	run_gamestate_img(t_table *table, mlx_image_t * img, int delay)
{
	if (get_time('a') - table->menudelaytime > delay)
	{
		table->main_menu_on = 1;
		img->instances[0].enabled = false;
		table->gameover_on = 0;
		table->gamewon_on = 0;
		table->controls_on = 0;
		display_main_menu(table);
	}
}