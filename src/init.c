/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/07 00:48:14 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_and_images(t_table *table)
{
	convert_texture(&table->no_texture, &table->no_texture.colors, table->no_path_texture);
	convert_texture(&table->so_texture, &table->so_texture.colors, table->so_path_texture);
	convert_texture(&table->es_texture, &table->es_texture.colors, table->es_path_texture);
	convert_texture(&table->ws_texture, &table->ws_texture.colors, table->ws_path_texture);
	convert_texture(&table->sprite_tx, &table->sprite_tx.colors, "pngs/sprite.png");
	convert_texture(&table->ball_texture, &table->ball_texture.colors, "pngs/ballsheet.png");
	convert_texture(&table->door_texture, &table->door_texture.colors, "pngs/door_0.png");
	convert_texture(&table->win_texture, &table->win_texture.colors, "pngs/win.png");
	table->right_hand = load_image(table->mlx_start, "pngs/rigth_hand.png");
	table->left_hand = load_image(table->mlx_start, "pngs/left_hand.png");
	table->mlx_2D = mlx_new_image(table->mlx_start, table->width, table->height);
	table->mlx_3D = mlx_new_image(table->mlx_start, table->width, table->height);
	table->ball_image = mlx_new_image(table->mlx_start, table->width, table->height);
	if (!table->mlx_2D || !table->mlx_3D || !table->ball_image)
	{
		printf("test \n");
		exit(EXIT_FAILURE);
	}
}

int	alloc_window_colors(t_table *table)
{
	int	i;

	table->w_colors = (uint32_t **)ft_calloc((table->height), sizeof(uint32_t *));
	if (!table->w_colors)
	{
		// free map
		printf("Memory allocation failed for rows\n");
		return (1);
	}
	i = -1;
	while (++i < table->height)
	{
		table->w_colors[i] = (uint32_t *)ft_calloc((table->width), sizeof(uint32_t));
		if (!table->w_colors[i])
		{
			// free previously allocated tiles, rows and map
			printf("Memory allocation failed for rows\n");
			return (1);
		}
	}
	return (0);
}

int	init_static_data(t_table *table, char ** argv)
{
	ft_memset(table, 0, sizeof(t_table));
	get_monitor_size(&table->width, &table->height);
	table->player_delta_x = cos((float)table->player_angle / 180 * PI);
	table->player_delta_y = sin((float)table->player_angle / 180 * PI);
	table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
	table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	table->lcg_seed = get_time('a');
	table->n_of_rays = table->width / 2;
	table->last_time = get_time('b');
	table->enemy_attack = 0;
	table->filename = argv[1];
	if (alloc_window_colors(table) == 1)
		return (1);
	return (0);
}

void	reset_doors(t_table *table)
{
	int y;
	int	x;

	y = -1;
	while (++y < (int)table->rows)
	{
		x = -1;
		while (++x < (int)table->columns)
		{
			if (table->map[y][x] == '3')
				table->map[y][x] = '2';
		}
	}
}

void	init_dynamic_data(t_table *table)
{
	if (table->player_dir == 'N')
		table->player_angle = 270;
	else if (table->player_dir == 'S')
		table->player_angle = 90;
	else if (table->player_dir == 'E')
		table->player_angle = 180;
	else if (table->player_dir == 'W')
		table->player_angle = 0;
	init_enemies(table);
	table->mouse_last_x = table->width / 2;
	table->mouse_last_y = table->height / 2;
	table->duplicate_id = 0;
	mlx_set_mouse_pos(table->mlx_start, table->width / 2, table->height / 2);
	table->kill = 0;
	table->sprite_frames = 0;
	int i = -1;
	while (++i < N_ENEMIES)
		table->enemies[i].dead = 0;
	table->player_x = (float)table->player_col * T_SIZE + T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE + T_SIZE / 2;
	reset_doors(table);
}
