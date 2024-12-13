/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state_images.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:01:20 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 11:45:38 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	display_controls(t_table *table)
{
	table->menudelaytime = get_time(table, 's');
	mlx_set_instance_depth(&table->controlsimg->instances[0], 15);
	table->controlsimg->instances[0].enabled = true;
	table->controls_on = 1;
}

void	display_gamewon(t_table *table)
{
	table->menudelaytime = get_time(table, 's');
	table->gamewonimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gamewonimg->instances[0], 15);
	table->gamewon_on = 1;
}

void	display_gameover(t_table *table)
{
	table->menudelaytime = get_time(table, 's');
	table->gameoverimg->instances[0].enabled = true;
	mlx_set_instance_depth(&table->gameoverimg->instances[0], 15);
	table->gameover_on = 1;
}

void	run_gamestate_img(t_table *table, mlx_image_t *img, int delay)
{
	if (get_time(table, 's') - table->menudelaytime > delay)
	{
		table->main_menu_on = 1;
		img->instances[0].enabled = false;
		table->gameover_on = 0;
		table->gamewon_on = 0;
		table->controls_on = 0;
		display_main_menu(table);
	}
}
