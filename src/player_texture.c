/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/11/20 15:16:01 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int animate_attack(t_table *table)
{
	table->frame_counter += 1;
	if (table->frame_counter % 3 == 0)
	{
		if (table->p_anim_index == 4)
		{
			mlx_resize_image(table->p_img[0], 300, 300);
			mlx_image_to_window(table->mlx_start, table->p_img[0], table->width / 2 - 150, table->height - 300);
			table->is_attacking = 0;
			table->p_anim_index = 0;
		}
		else
		{
			mlx_resize_image(table->p_img[table->p_anim_index], 300, 300);
			mlx_image_to_window(table->mlx_start, table->p_img[table->p_anim_index], table->width / 2 - 150, table->height - 300);
			table->p_anim_index += 1;
		}
	}
	return (0);
}

int	insert_player_texture(t_table *table)
{
	mlx_resize_image(table->p_img[table->p_anim_index], 300, 300);
	mlx_image_to_window(table->mlx_start, table->p_img[0], table->width / 2 - 150, table->height - 300);
	//mlx_set_instance_depth(&table->p_img->instances[index], 1);
	return (0);
}