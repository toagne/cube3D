/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/05 09:44:50 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main (int argc, char **argv)
{
	t_table	table;

	(void) argc;
	(void) argv;
	ft_memset(&table, 0, sizeof(table));
	table.enemy_attack = 0;
	if (argc != 2)
	{
		//write (2, "wrong input\n", 12);
		exit(EXIT_FAILURE);
	}
	// check that argc 1 is a file that can be opened and read and ends with .cub
	//parse_input();
	init_static_data(&table);
	table.filename = argv[1];
	if (read_file(&table))
	{
		return (1);
	}
	table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
	if (!table.mlx_start)
	{
		;//error
	}
	add_doors(&table);
	init_dynamic_data(&table);
	init_main_menu(&table);
	convert_texture(&table.no_texture, &table.no_texture.colors, "pngs/texture_no.png");
	convert_texture(&table.so_texture, &table.so_texture.colors, "pngs/texture_so.png");
	convert_texture(&table.es_texture, &table.es_texture.colors, "pngs/texture_es.png");
	convert_texture(&table.ws_texture, &table.ws_texture.colors, "pngs/texture_ws.png");
	convert_texture(&table.sprite_tx, &table.sprite_tx.colors, "pngs/enemy.png");
	convert_texture(&table.ball_texture, &table.ball_texture.colors, "pngs/ballsheet.png");
	convert_texture(&table.door_texture, &table.door_texture.colors, "pngs/Door02.png");
	table.right_hand = load_image(table.mlx_start, "pngs/rigth_hand.png");
	table.left_hand = load_image(table.mlx_start, "pngs/left_hand.png");
	table.mlx_2D = mlx_new_image(table.mlx_start, table.width, table.height); //to change
	if (!table.mlx_2D)
	{
		;//error
	}
	table.mlx_3D = mlx_new_image(table.mlx_start, table.width, table.height);
	table.ball_image = mlx_new_image(table.mlx_start, table.width, table.height);
	if (!table.mlx_3D)
	{
		;//error
	}
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
