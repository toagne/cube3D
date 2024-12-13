/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/13 10:52:35 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_custom_images(t_table *table)
{
	if (init_main_menu(table))
	{
		free_all(table);
		exit(EXIT_FAILURE);
	}
	if (init_gameover(table))
	{
		free_all(table);
		exit(EXIT_FAILURE);
	}
	if (init_gamewon(table))
	{
		free_all(table);
		exit(EXIT_FAILURE);
	}
	if (init_controls(table))
	{
		free_all(table);
		exit(EXIT_FAILURE);
	}
}

void	init(t_table *table)
{
	if (init_static_data(table) == 1)
	{
		free_all(table);
		exit(EXIT_FAILURE);
	}
	add_doors(table);
	get_random_win_spot(table);
	init_dynamic_data(table);
	init_custom_images(table);
}

void	images_to_window(t_table *table)
{
	if (mlx_image_to_window(table->mlx_start, table->mlx_raycast, 0, 0) == -1)
	{
		ft_error("setting raycast image failed", table);
		free_all(table);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(table->mlx_start, table->mlx_minimap, 0, 0) == -1)
	{
		ft_error("setting minimap image failed", table);
		free_all(table);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(table->mlx_start, table->ball_image, 0, 0) == -1)
	{
		ft_error("setting ball image failed", table);
		free_all(table);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (argc != 2)
	{
		ft_error("wrong number of arguments", &table);
		exit(EXIT_FAILURE);
	}
	table.filename = argv[1];
	if (read_file(&table))
	{
		free_all(&table);
		exit(EXIT_FAILURE);
	}
	init(&table);
	images_to_window(&table);
	insert_player_texture(&table);
	mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
	mlx_loop_hook(table.mlx_start, &ft_hook, &table);
	mlx_loop_hook(table.mlx_start, &ft_mouse, &table);
	mlx_loop(table.mlx_start);
	free_all(&table);
	exit (EXIT_SUCCESS);
}
