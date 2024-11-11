/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/11 16:40:00 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_table	*table;

	table = (t_table *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(table->mlx_start);
		exit (EXIT_SUCCESS);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		table->player_y-=5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		table->player_y+=5;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		table->player_x+=5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		table->player_x-=5;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		table->player_angle -= 0.1;
		if (table->player_angle < 0)
			table->player_angle += 2 * PI;
		table->player_delta_x = cos(table->player_angle) * 20;
		table->player_delta_y = sin(table->player_angle) * 20;
	}
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		table->player_angle += 0.1;
		if (table->player_angle > 2 * PI)
			table->player_angle -= 2 * PI;
		table->player_delta_x = cos(table->player_angle) * 20;
		table->player_delta_y = sin(table->player_angle) * 20;
	}
	draw_map(table);
	draw_player(table);
}
