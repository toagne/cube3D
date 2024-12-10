/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 15:14:22 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_side_wall(t_table *table, t_texture *tx, float dx, float dy)
{
	if (dy > dx && dy > (T_SIZE - dx))
	{
		tx->height = table->no_texture.height;
		tx->width = table->no_texture.width;
		tx->colors = table->no_texture.colors;
	}
	else if (dy < dx && dy < (T_SIZE - dx))
	{
		tx->height = table->so_texture.height;
		tx->width = table->so_texture.width;
		tx->colors = table->so_texture.colors;
	}
	else if (dx <= dy && dx <= (T_SIZE - dy))
	{
		tx->height = table->es_texture.height;
		tx->width = table->es_texture.width;
		tx->colors = table->es_texture.colors;
	}
	else
	{
		tx->height = table->ws_texture.height;
		tx->width = table->ws_texture.width;
		tx->colors = table->ws_texture.colors;
	}
}

void	select_texture(t_table *table, t_texture *tx)
{
	int			tile_x;
	int			tile_y;

	tile_x = (int)(table->ray.f_x / T_SIZE) * T_SIZE;
	tile_y = (int)(table->ray.f_y / T_SIZE) * T_SIZE;
 	if (table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '2')
	{
		tx->height = table->door_texture.height;
		tx->width = table->door_texture.width;
		tx->colors = table->door_texture.colors;
		return ;
	}
	if (table->map[tile_y / T_SIZE][tile_x / T_SIZE] == '4')
	{
		tx->height = table->win_texture.height;
		tx->width = table->win_texture.width;
		tx->colors = table->win_texture.colors;
		return ;
	}
	table->ray.dx_for_wall = table->ray.f_x - tile_x;
	table->ray.dy_for_wall = table->ray.f_y - tile_y;
	check_side_wall(table, tx, table->ray.dx_for_wall, table->ray.dy_for_wall);
}

void	get_coordinates_in_texture(t_table *table)
{
	table->ray.ty = table->ray.tx_v_offset * table->ray.tx_v_step;
	if (table->ray.v_v > table->ray.h_v)
	{
		table->ray.tx = ((int)table->ray.f_x % T_SIZE)
			* table->ray.texture.width / T_SIZE;
		if (table->ray.dy_for_wall < table->ray.dx_for_wall
			&& table->ray.dy_for_wall < (T_SIZE - table->ray.dx_for_wall))
		{
			if (table->ray.tx == 0)
				table->ray.tx = table->ray.texture.width;
			table->ray.tx = table->ray.texture.width - table->ray.tx;
		}
	}
	else
	{
		table->ray.tx = ((int)table->ray.f_y % T_SIZE)
			* table->ray.texture.width / T_SIZE;
		if (table->ray.dx_for_wall >= table->ray.dy_for_wall
			&& table->ray.dx_for_wall >= (T_SIZE - table->ray.dy_for_wall))
		{
			if (table->ray.tx == 0)
				table->ray.tx = table->ray.texture.width;
			table->ray.tx = table->ray.texture.width - table->ray.tx;
		}
	}
}
