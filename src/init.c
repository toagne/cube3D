/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 15:12:02 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_and_images(t_table *t)
{
	convert_tx(&t->no_texture, &t->no_texture.colors, "pngs/texture_no.png");
	convert_tx(&t->so_texture, &t->so_texture.colors, "pngs/texture_so.png");
	convert_tx(&t->es_texture, &t->es_texture.colors, "pngs/texture_es.png");
	convert_tx(&t->ws_texture, &t->ws_texture.colors, "pngs/texture_ws.png");
	convert_tx(&t->sprite_tx, &t->sprite_tx.colors, "pngs/sprite.png");
	convert_tx(&t->ball_texture, &t->ball_texture.colors, "pngs/ballsheet.png");
	convert_tx(&t->door_texture, &t->door_texture.colors, "pngs/door_0.png");
	convert_tx(&t->win_texture, &t->win_texture.colors, "pngs/win.png");
	t->right_hand = load_image(t->mlx_start, "pngs/rigth_hand.png");
	t->left_hand = load_image(t->mlx_start, "pngs/left_hand.png");
	t->mlx_minimap = mlx_new_image(t->mlx_start, t->width, t->height);
	t->mlx_raycast = mlx_new_image(t->mlx_start, t->width, t->height);
	t->ball_image = mlx_new_image(t->mlx_start, t->width, t->height);
	if (!t->mlx_minimap || !t->mlx_raycast || !t->ball_image)
	{
		exit (EXIT_FAILURE);//error
	}
}

int	alloc_window_colors(t_table *t)
{
	int	i;

	t->w_colors = (uint32_t **)ft_calloc((t->height), sizeof(uint32_t *));
	if (!t->w_colors)
	{
		// free map
		printf("Memory allocation failed for rows\n");
		return (1);
	}
	i = -1;
	while (++i < t->height)
	{
		t->w_colors[i] = (uint32_t *)ft_calloc((t->width), sizeof(uint32_t));
		if (!t->w_colors[i])
		{
			// free previously allocated tiles, rows and map
			printf("Memory allocation failed for rows\n");
			return (1);
		}
	}
	return (0);
}

int	init_static_data(t_table *t, char **argv)
{
	ft_memset(t, 0, sizeof(t_table));
	get_monitor_size(&t->width, &t->height);
	t->player_delta_x = cos((float)t->player_angle / 180 * PI);
	t->player_delta_y = sin((float)t->player_angle / 180 * PI);
	t->player_delta_x_ad = cos((float)(t->player_angle + 90) / 180 * PI);
	t->player_delta_y_ad = sin((float)(t->player_angle + 90) / 180 * PI);
	t->lcg_seed = get_time('a');
	t->n_of_rays = t->width / 2;
	t->last_time = get_time('b');
	t->enemy_attack = 0;
	t->filename = argv[1];
	if (alloc_window_colors(t) == 1)
		return (1);
	return (0);
}

void	reset_doors(t_table *table)
{
	int	y;
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
	int	i;

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
	i = -1;
	while (++i < N_ENEMIES)
		table->enemies[i].dead = 0;
	table->player_x = (float)table->player_col * T_SIZE + T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE + T_SIZE / 2;
	reset_doors(table);
}
