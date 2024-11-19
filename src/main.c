/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 20:17:40 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main (int argc, char **argv)
{
	t_table	table;

	(void) argc;
	(void) argv;
	if (argc != 2)
	{
		write (2, "wrong input\n", 12);
		exit(EXIT_FAILURE);
	}
	// check that argc 1 is a file that can be opened and read and ends with .cub
	//parse_input();
	init_data(&table);
	table.filename = argv[1];
	read_map(&table);
	if (!validate_map(&table))
		return (1);
	get_monitor_size(&table.width, &table.height);
	table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
	if (!table.mlx_start)
	{
		;//error
	}
	convert_texture(&table.no_texture, &table.no_texture_colors, "pngs/texture_no.png");
	convert_texture(&table.so_texture, &table.so_texture_colors, "pngs/texture_so.png");
	convert_texture(&table.es_texture, &table.es_texture_colors, "pngs/texture_es.png");
	convert_texture(&table.ws_texture, &table.ws_texture_colors, "pngs/texture_ws.png");
	table.mlx_2D = mlx_new_image(table.mlx_start, table.width / 5, table.height / 5);
	if (!table.mlx_2D)
	{
		;//error
	}
	table.mlx_3D = mlx_new_image(table.mlx_start, table.width, table.height);
	if (!table.mlx_3D)
	{
		;//error
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

	/*y = -1;
	while (++y < table.es_texture->height)
	{
		x = -1;
		while (++x < table.es_texture->width)
			mlx_put_pixel(table.mlx_3D, x, y, table.es_texture_colors[y][x]);
	}
	mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);*/
	draw_minimap(&table);
	draw_raycasting(&table);
	mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
	mlx_loop(table.mlx_start);
}
