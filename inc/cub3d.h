/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/16 18:36:44 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h> 
# include <MLX42/MLX42.h>
# include "../libft/libft.h"

# define PI 3.14159265358979323846
# define T_SIZE 64

typedef struct s_table
{
	mlx_t			*mlx_start;
	mlx_image_t		*mlx_2D;
	mlx_image_t		*mlx_3D;
	int				width;
	int				height;
	char			*filename;
	char			**map;
	size_t			columns;
	size_t			rows;
	float			player_x;
	float			player_y;
	float			player_angle;
	float			player_delta_x;
	float			player_delta_y;
	int				player_col;
	int				player_row;
	int				player;
	float			player_delta_x_ad;
	float			player_delta_y_ad;
	char			*no_path_texture;
	char			*so_path_texture;
	char			*es_path_texture;
	char			*ws_path_texture;
	mlx_texture_t	*no_texture;
	mlx_image_t		*no_image;
	mlx_texture_t	*so_texture;
	mlx_image_t		*so_image;
	mlx_texture_t	*es_texture;
	mlx_image_t		*es_image;
	mlx_texture_t	*ws_texture;
	mlx_image_t		*ws_image;
	uint32_t		es_texture_colors[1100][1100];
}   t_table;

void	init_data(t_table *table);
void	ft_keyboard(mlx_key_data_t keydata, void *param);

void	draw_map(t_table *table);
void	draw_player(t_table *table);

// read_map.c
int		read_map(t_table *table);

// error.c
void    ft_error(char *s1);

// validate_map.c
int		validate_map(t_table *table);

// load_images.c
mlx_image_t *load_image(mlx_t *mlx, char *str);
mlx_texture_t *load_texture(char *str);

#endif
