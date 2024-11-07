/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/07 14:10:33 by mpellegr         ###   ########.fr       */
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

# define PI 3.14159265358979323846

typedef struct s_table
{
    mlx_t			*mlx_start;
	mlx_image_t		*mlx_image;
    int             width;
    int             height;
    int             map_fd;
    char            map[1024];
    int             columns;
    int             rows;
    float           player_x;
    float           player_y;
    float           player_angle;
    float           player_delta_x;
    float           player_delta_y;
}   t_table;

void    init_data(t_table *table);
void    ft_keyboard(mlx_key_data_t keydata, void *param);

void    draw_map(t_table *table);
void    draw_player(t_table *table);

#endif