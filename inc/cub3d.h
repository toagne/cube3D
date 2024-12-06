/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:20:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/06 16:10:43 by giuls            ###   ########.fr       */
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
# include <sys/time.h>
# include <float.h>
# include "../libft/libft.h"

# define PI 3.14159265358979323846
# define T_SIZE 64
# define N_ENEMIES 10

typedef	struct	s_door
{
	int	x;
	int	y;
	int	room_1;
	int	room_2;
} t_door;

typedef	struct	s_enemy
{
	float		x;
	float		y;
	float	dist;
	float	dx;
	float	dy;
	float	angle;
	float	screen_size;
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;
	int		tx_start_x;
	int		dead;
	int		pending_death;
} t_enemy;

typedef	struct	s_texture
{
	uint32_t	width;
	uint32_t	height;
	uint32_t	**colors;
	
} t_texture;

typedef	struct	s_ray
{
	float		v_x;
	float		v_y;
	float		v_v;
	float		h_x;
	float		h_y;
	float		h_v;
	float		f_x;
	float		f_y;
	float		f_v;
	t_texture	texture;
	int 		wall_h;
	float		tx_v_step;
	float		tx_v_offset;
	int			start_wall;
	int			end_wall;
	int			x_start;
	int			x_end;
	float		tx;
	float		ty;
} t_ray;

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
	t_texture		no_texture;
	t_texture		so_texture;
	t_texture		es_texture;
	t_texture		ws_texture;
	t_texture		ball_texture;
	t_texture		door_texture;
	// mlx_texture_t	*ball_texture;
	// uint32_t		**ball_texture_colors;
	mlx_image_t		*ball_image;
	t_enemy			enemies[N_ENEMIES];
	mlx_texture_t	*enemy_texture;
	uint32_t		**enemy_texture_colors;
	long			lcg_seed;
	t_ray			ray;
	int				n_of_rays;
	t_texture		sprite_tx;
	int				main_menu_on;
	int32_t			x_mouse;
	int32_t			y_mouse;
	t_button		play_button;
	t_button		exit_button;
	mlx_image_t		*bg_img;
	long			last_time;
	uint32_t		**w_colors;
	int				mouse_last_x;
	int				mouse_last_y;
	int				kill;
	int				sprite_frames;
	long			menudelaytime;
	mlx_image_t		*gameoverimg;
	mlx_image_t		*gamewonimg;
	int				gameover_on;
	int				gamewon_on;
}	t_table;

// init.c
int				init_static_data(t_table *table, char **argv);
void			init_dynamic_data(t_table *table);
void			init_texture_and_images(t_table *table);

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
int				read_map(t_table *table, int fd, char *line);

// error.c
void    		ft_error(char *s1);

// validate_map.c
int				validate_map(t_table *table);

// load_images.c
mlx_image_t 	*load_image(mlx_t *mlx, char *str);
mlx_texture_t 	*load_texture(char *str);
void			convert_texture(t_texture *tx, uint32_t ***tx_colors, char *str);

unsigned int	get_rgba(int r, int g, int b, int a);
void			get_monitor_size(int *width, int *height);
float			deg_to_rad(float deg);
long			get_time(char type);

void			draw_minimap(t_table *table);
void			convert_rays_for_minimap(t_table *table, float angle, float ray_angle);

// read_file.c
int				read_file(t_table *table);

// free.c
void			free_map(char **map, size_t i);
void			free_table(char ***table);
 
// main_menu
void init_main_menu(t_table *table);
void animate_button(t_button *button);
void ft_mouse(void *param);
void	display_main_menu(t_table *table);
void	undisplay_main_menu(t_table *table);
void	display_gameover(t_table *table);
void	display_gamewon(t_table *table);
void	init_gameover(t_table *table);
void	init_gamewon(t_table *table);
void	run_gamestate_img(t_table *table, mlx_image_t * img);

void			ft_hook(void* param);

void	draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color);

void init_enemies(t_table *table);
int	insert_fireball(t_table *table);

void	draw_sprites(t_table *table);

void	draw_dot(t_table *table, int value_x, int value_y, int range);
void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color, t_table *table, int type);

void	check_vertical_lines(t_table *table, float angle);
void	check_horizontal_lines(t_table *table, float angle);
void	chose_shortest_ray(t_table *table);

void	select_texture(t_table *table, t_texture *tx);
void	get_coordinates_in_texture(t_table *table);

void	convert_sprite_sizes(t_table *table, float angle_diff, t_enemy *sp);
int		check_sprite_is_visible(t_table *table, t_enemy sp);

void	add_doors(t_table *table);

#endif
