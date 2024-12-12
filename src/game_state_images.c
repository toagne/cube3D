/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state_images.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:01:20 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 09:38:08 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	display_gamewon(t_table *table)
{
	table->menudelaytime = get_time('s');
	table->gamewonimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gamewonimg->instances[0], 13);
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
	table->menudelaytime = get_time('s');
	table->gameoverimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gameoverimg->instances[0], 13);
	table->gameover_on = 1;
}

void	run_gamestate_img(t_table *table, mlx_image_t * img)
{
	if (get_time('s') - table->menudelaytime > 3)
	{
		table->main_menu_on = 1;
		img->instances[0].enabled = false;
		table->gameover_on = 0;
		table->gamewon_on = 0;
		display_main_menu(table);
	}
}
