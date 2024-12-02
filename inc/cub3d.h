/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/28 10:58:09 by mpellegr         ###   ########.fr       */
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
# define N_ENEMIES 10

typedef	struct	s_enemy
{
	int		x;
	int		y;
	float	dist;
} t_enemy;

typedef struct s_button
{
	mlx_image_t *colored;
	mlx_image_t *white;
	int			status;
} t_button;

typedef struct s_table
{
	mlx_t			*mlx_start;
	mlx_image_t		*mlx_2D;
	mlx_image_t		*mlx_3D;
	int				duplicate_id;	/// checking for duplicate identifiers in the .cub file
	int				frame_counter;
	int				is_attacking;
	int				enemy_attack;
	int				width;
	int				height;
	char			*filename;
	char			**map;
	char			player_dir;
	int				p_anim_index;
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
	char			*es_path_texture;
	char			*ws_path_texture;
	char			*p_path_texture;
	mlx_image_t		*p_img[30];
	mlx_image_t		*left_hand;
	mlx_image_t		*right_hand;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*es_texture;
	mlx_texture_t	*ws_texture;
	uint32_t		**no_texture_colors;
	uint32_t		**so_texture_colors;
	uint32_t		**es_texture_colors;
	uint32_t		**ws_texture_colors;
	mlx_texture_t	*ball_texture;
	uint32_t		**ball_texture_colors;
	mlx_image_t		*ball_image;
	int				sprite_x;
	int				sprite_y;
	int				x_aligned_flag;
	int				y_stuck;
	int				y_aligned_flag;
	int				e_spawn_pos_x;
	int				e_spawn_pos_y;
	t_enemy			enemies[N_ENEMIES];
	mlx_texture_t	*enemy_texture;
	uint32_t		**enemy_texture_colors;
	long			lcg_seed;
	int				main_menu_on;
	int32_t			x_mouse;
	int32_t			y_mouse;
	t_button		play_button;
	t_button		exit_button;
}	t_table;

void			init_data(t_table *table);
void			ft_keyboard(mlx_key_data_t keydata, void *param);
void			ft_hook(void* param);
void			ft_enemy(void *param);
void			update_enemy_positions(t_table *table);
void			set_image_instance_pos(mlx_instance_t *instance, int x, int y);

// player_texture.
int				insert_player_texture(t_table *table);
int 			animate_attack(t_table *table);
int				animate_enemy(t_table *table);

void			draw_raycasting(t_table *table);

// read_map.c
int				read_map(t_table *table, int fd);

// error.c
void    		ft_error(char *s1);

// validate_map.c
int				validate_map(t_table *table);

// load_images.c
mlx_image_t 	*load_image(mlx_t *mlx, char *str);
mlx_texture_t 	*load_texture(char *str);
void			convert_texture(mlx_texture_t **tx, uint32_t ***tx_colors, char *str);

unsigned int	get_rgba(int r, int g, int b, int a);
void			get_monitor_size(int *width, int *height);
float			deg_to_rad(float deg);

void			draw_minimap(t_table *table);

// read_file.c
int				read_file(t_table *table);

// free.c
void			free_map(char **map, size_t i);
void			free_table(char ***table);
 
// main_menu
void			main_menu(t_table *table);
void			animate_button(t_button *button);
void			ft_mouse(void *param);

void			ft_hook(void* param);

void	draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color);

void init_enemies(t_table *table);
int	insert_fireball(t_table *table);

#endif
