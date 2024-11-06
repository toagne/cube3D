/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/06 11:44:42 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>

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
}   t_table;

void    init_data(t_table *table);
void    ft_keyboard(mlx_key_data_t keydata, void *param);

#endif