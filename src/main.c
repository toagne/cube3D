/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/06 12:40:55 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main (int argc, char **argv)
{
	t_table	table;
	
	if (argc != 2)
	{
		//write (2, "wrong input\n", 12);
		exit(EXIT_FAILURE);
	}
	if (init_static_data(&table, argv) == 1)
		exit(EXIT_FAILURE);
	if (read_file(&table))
		exit(EXIT_FAILURE);
	table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
	if (!table.mlx_start)
	{
		;//error
	}
	add_doors(&table);
	init_dynamic_data(&table);
	init_main_menu(&table);
	init_gameover(&table);
	init_gamewon(&table);
	init_texture_and_images(&table);
	mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);
	mlx_image_to_window(table.mlx_start, table.mlx_2D, 0, 0);
	mlx_image_to_window(table.mlx_start, table.ball_image, 0, 0);
	insert_player_texture(&table);
	mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
	mlx_loop_hook(table.mlx_start, &ft_hook, &table);
	mlx_loop_hook(table.mlx_start, &ft_mouse, &table);
	mlx_loop(table.mlx_start);
}

// ---how to scale a texture---
/*int h = 300;
int w = 300;
float sh = (float)table.es_texture->height / h;
float sw = (float)table.es_texture->width / w;
printf("sh = %f\n", sh);
printf("sw = %f\n", sw);
int a = -1;
float c = 0;
while (++a < h)
{
	int b = -1;
	float d = 0;
	while (++b < w)
	{
		int tex_c = (int)c;
		int tex_d = (int)d;
		mlx_put_pixel(table.mlx_3D, b, a, table.es_texture_colors[tex_c][tex_d]);
		d += sw;
		printf("%d\n", tex_d);
	}
	c += sh;
}
mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);*/
