/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/14 15:19:51 by mpellegr         ###   ########.fr       */
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
	int				*f_color;
	int				*c_color;
	char			*no_path_texture;
	char			*so_path_texture;
	char			*ea_path_texture;
	char			*we_path_texture;
	mlx_texture_t	*no_texture;
	mlx_image_t		*no_image;
	mlx_texture_t	*so_texture;
	mlx_image_t		*so_image;
	mlx_texture_t	*ea_texture;
	mlx_image_t		*ea_image;
	mlx_texture_t	*we_texture;
	mlx_image_t		*we_image;
}   t_table;

void	init_data(t_table *table);
void	ft_keyboard(mlx_key_data_t keydata, void *param);

void	draw_map(t_table *table);
void	draw_player(t_table *table);

// read_map.c
int		read_map(t_table *table, int fd);

// error.c
void    ft_error(char *s1);

// validate_map.c
int		validate_map(t_table *table);

// load_images.c
mlx_image_t *load_image(mlx_t *mlx, char *str);

// read_file.c
int	read_file(t_table *table);

// free.c
void	free_map(char **map, size_t i);
void	free_table(char ***table);

#endif
