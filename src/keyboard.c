/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/05 18:42:19 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int circle_rectangle_collision(int circle_x, int circle_y, int radius, int rect_x, int rect_y, int rect_size)
{
	// Find the closest point on the rectangle to the circle
	int closest_x = fmax(rect_x, fmin(circle_x, rect_x + rect_size));
	int closest_y = fmax(rect_y, fmin(circle_y, rect_y + rect_size));

	// Calculate distance from circle's center to closest point
	int dx = circle_x - closest_x;
	int dy = circle_y - closest_y;

	// Check if the distance is less than the circle's radius
	return (dx * dx + dy * dy) < (radius * radius);
}


int	wall_collision_w_circular_bumper(t_table *table, int new_x, int new_y, int boh_x, int boh_y, int radius)
{
	// int	radius;
	//int new_x;
	//int	new_y;
	int	mpx;
	int	mpy;
	int x;
	int y;
	int check_tile_x;
	int	check_tile_y;
	int wall_x;
	int	wall_y;
	//int	offset;

	//radius = 20;// + T_SIZE / 2;
	//new_x = table->player_x + table->player_delta_x * 5;
	//new_y = table->player_y + table->player_delta_y * 5;
	mpx = boh_x / T_SIZE;
	mpy = boh_y / T_SIZE;
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			check_tile_x = mpx + x;
			check_tile_y = mpy + y;
			if (check_tile_x >= 0 && check_tile_x < (int)table->columns && check_tile_y >= 0 && check_tile_y < (int)table->rows)
			{
				if (table->map[check_tile_y][check_tile_x] == '1' || table->map[check_tile_y][check_tile_x] == '2')
				{
					if (radius == 10 && table->map[check_tile_y][check_tile_x] == '2')
							table->map[check_tile_y][check_tile_x] = '0';
					//printf("tile x = %d	tile y = %d\n", check_tile_x, check_tile_y);
					wall_x = check_tile_x * T_SIZE;// + T_SIZE / 2;
					wall_y = check_tile_y * T_SIZE;// + T_SIZE / 2;
					//offset = (new_x - wall_x) * (new_x - wall_x) + (new_y - wall_y) * (new_y - wall_y);
					//printf("offset = %d\n", offset);
					//printf("r2 = %d\n", radius * radius);
					//if (offset < radius * radius)
					//	return (1);
					if (circle_rectangle_collision(new_x, new_y, radius, wall_x, wall_y, T_SIZE))
						return 1;
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	move_visual_with_mouse(t_table *table)
{
	int	delta_x_mouse;

	mlx_set_cursor_mode(table->mlx_start, MLX_MOUSE_HIDDEN);
	delta_x_mouse = table->x_mouse - table->mouse_last_x;
	if (delta_x_mouse != 0)
	{
		table->player_angle += delta_x_mouse * 0.5;
		if (table->player_angle < 0)
			table->player_angle += 360;
		if (table->player_angle >= 360)
			table->player_angle -= 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
		mlx_set_mouse_pos(table->mlx_start, table->width / 2, table->height / 2);
		table->mouse_last_x = table->width / 2;
		table->mouse_last_y = table->height / 2;
	}
}

void ft_mouse(void *param)
{
	t_table		*table;
	table = (t_table *)param;
	mlx_get_mouse_pos(table->mlx_start, &table->x_mouse, &table->y_mouse);
	if (table->main_menu_on == 0)
	{
		move_visual_with_mouse(table);
		return ;
	}
	if (table->x_mouse > table->play_button.white->instances[0].x && table->x_mouse < table->play_button.white->instances[0].x + table->width / 6 \
	&& table->y_mouse > table->play_button.white->instances[0].y && table->y_mouse < table->play_button.white->instances[0].y + table->height / 6)
	{
		table->play_button.status = 0;
		animate_button(&table->play_button);
		if (mlx_is_mouse_down(table->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{	
			table->main_menu_on = 0;
			undisplay_main_menu(table);
			return ;
		}
	}
	else
	{
		table->play_button.status = 1;
		animate_button(&table->play_button);
	}
	if (table->x_mouse > table->exit_button.white->instances[0].x && table->x_mouse < table->exit_button.white->instances[0].x + table->width / 6 \
	&& table->y_mouse > table->exit_button.white->instances[0].y && table->y_mouse < table->exit_button.white->instances[0].y + table->height / 6)
	{
		table->exit_button.status = 0;
		animate_button(&table->exit_button);
		if (mlx_is_mouse_down(table->mlx_start, MLX_MOUSE_BUTTON_LEFT))
		{
			mlx_terminate(table->mlx_start);
			exit (EXIT_SUCCESS);
		}
	}
	else
	{
		table->exit_button.status = 1;
		animate_button(&table->exit_button);
	}

}

void	kill_sprite(t_table *table)
{
	int		i;
	int		dx;
	int		dy;
	float	angle_to_enemy;
	float	angle_diff;
	float	ray;
	float	closest_ray;
	int		closest_enemy_index;

	closest_enemy_index = -1;
	closest_ray = FLT_MAX;
	i = -1;
	while (++i < N_ENEMIES)
	{
		if (table->enemies[i].dead)
			continue ;
		dx = table->enemies[i].x - table->player_x;
		dy = table->enemies[i].y - table->player_y;
		ray = sqrt((dx * dx) + (dy * dy));
		angle_to_enemy = atan2(dy, dx) * 180 / PI;
		angle_diff = table->player_angle - angle_to_enemy;
		if (angle_diff > 180)
			angle_diff -= 360;
		if (angle_diff < -180)
			angle_diff += 360;
		if (fabs(angle_diff) <= 10)
		{
			check_vertical_lines(table, deg_to_rad(angle_to_enemy));
			check_horizontal_lines(table, deg_to_rad(angle_to_enemy));
			chose_shortest_ray(table);
			if (ray <= table->ray.f_v && ray < closest_ray)
			{
					closest_ray = ray;
					closest_enemy_index = i;
			}
		}
	}
	if (closest_enemy_index != -1)
	{
		int i = closest_enemy_index;
		table->enemies[i].pending_death = 1;
		table->enemies[i].dead = 1;
		table->enemies[i].x = 0;
		table->enemies[i].y = 0;
		table->kill = 0;
	}
}

void ft_hook(void* param)
{
	t_table	*table;
	//int	avoid_wall_collision;
	float		new_x;
	float		new_y;
	int		render_flag = 0;

	table = (t_table *)param;

	// --------------------- normalizing speed ------------------------
	long	current_time = get_time('b');
	//printf("ct = %ld\n", current_time);
	//printf("lt = %ld\n", table->last_time);
	long	delta_time = current_time - table->last_time;
	table->last_time = current_time;
	//printf("dt = %ld\n", delta_time);
	float d_t_in_s = (float)delta_time / 1000000;
	//printf("dt in s = %f\n", d_t_in_s);
	if (table->gameover_on == 1)
	{
		run_gamestate_img(table, table->gameoverimg);
		return ;
	}
	if (table->gamewon_on == 1)
	{
		run_gamestate_img(table, table->gamewonimg);
		return ;
	}
	if (table->main_menu_on)
		return ;
	table->frame_counter += 1;
	table->left_hand->instances[0].enabled = true;
	table->right_hand->instances[0].enabled = true;
	table->ball_image->instances[0].enabled = true;
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_W))
	{
		render_flag = 1;
		new_x = table->player_x + table->player_delta_x * d_t_in_s * 150;
		new_y = table->player_y + table->player_delta_y * d_t_in_s * 150;
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y, table->player_x, table->player_y, 10))
		//if (table->map[mpy][mpxcw] != '1')
			table->player_x = new_x;
		//if (table->map[mpycw][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y, table->player_x, table->player_y, 10))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_S))
	{
		render_flag = 1;
		new_x = table->player_x - table->player_delta_x * d_t_in_s * 150;
		new_y = table->player_y - table->player_delta_y * d_t_in_s * 150;
		//if (table->map[mpy][mpxcs] != '1')
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y, table->player_x, table->player_y, 10))
			table->player_x = new_x;
		//if (table->map[mpycs][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y, table->player_x, table->player_y, 10))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_D))
	{
		render_flag = 1;
		new_x = table->player_x + table->player_delta_x_ad * d_t_in_s * 150;
		new_y = table->player_y + table->player_delta_y_ad * d_t_in_s * 150;
		//if (table->map[mpy][mpxcd] != '1')
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y, table->player_x, table->player_y, 10))
			table->player_x = new_x;
		//if (table->map[mpycd][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y, table->player_x, table->player_y, 10))
			table->player_y  = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_A))
	{
		render_flag = 1;
		new_x = table->player_x - table->player_delta_x_ad * d_t_in_s * 150;
		new_y = table->player_y - table->player_delta_y_ad * d_t_in_s * 150;
		//if (table->map[mpy][mpxca] != '1')
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y, table->player_x, table->player_y, 10))
			table->player_x = new_x;
		//if (table->map[mpyca][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y, table->player_x, table->player_y, 10))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_LEFT))
	{
		render_flag = 1;
		table->player_angle -= d_t_in_s * 150;
		if (table->player_angle < 0)
			table->player_angle += 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_RIGHT))
	{
		render_flag = 1;
		table->player_angle += d_t_in_s * 150;
		if (table->player_angle > 359)
			table->player_angle -= 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	}
	
	// int offset = 32;
	// int sprite_x_map = table->enemies[i].x / T_SIZE;
	// int e_spawn_pos_y_map = table->enemies[i].y / T_SIZE;
	// int sprite_x_map_add = (table->enemies[i].x + offset) / T_SIZE;
	// int e_spawn_pos_y_map_add = (table->enemies[i].y + offset) / T_SIZE;
	// int sprite_x_map_sub = (table->enemies[i].x - offset) / T_SIZE;
	// int e_spawn_pos_y_map_sub = (table->enemies[i].y - offset) / T_SIZE;
	//printf("%d	%d\n", sprite_x_map, e_spawn_pos_y_map);

	// if (table->enemies[i].x < table->player_x && table->enemies[i].y < table->player_y && table->map[e_spawn_pos_y_map_add][sprite_x_map_add] != '1' && table->map[e_spawn_pos_y_map_sub][sprite_x_map_add] != '1' && table->map[e_spawn_pos_y_map][sprite_x_map_add] != '1') // down - right
	// {
	// 	table->enemies[i].x += 1;
	// 	table->enemies[i].y += 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].x < table->player_x && table->enemies[i].y > table->player_y && table->map[e_spawn_pos_y_map_sub][sprite_x_map_add] != '1' && table->map[e_spawn_pos_y_map_add][sprite_x_map_add] != '1') // up - right
	// {
	// 	table->enemies[i].x += 1;
	// 	table->enemies[i].y -= 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].x > table->player_x && table->enemies[i].y < table->player_y && table->map[e_spawn_pos_y_map_add][sprite_x_map_sub] != '1') // down - left
	// {
	// 	table->enemies[i].x -= 1;
	// 	table->enemies[i].y += 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].x > table->player_x && table->enemies[i].y > table->player_y && table->map[e_spawn_pos_y_map_sub][sprite_x_map_sub] != '1') // up - left
	// {
	// 	table->enemies[i].x -= 1;
	// 	table->enemies[i].y -= 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].x < table->player_x && table->map[e_spawn_pos_y_map][sprite_x_map_add] != '1') // right
	// {
	// 	table->enemies[i].x += 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].x > table->player_x && table->map[e_spawn_pos_y_map][sprite_x_map_sub] != '1') // left
	// {
	// 	table->enemies[i].x -= 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].y < table->player_y && table->map[e_spawn_pos_y_map_add][sprite_x_map] != '1') // down
	// {
	// 	table->enemies[i].y += 1;
	// 	render_flag = 1;
	// }
	// else if (table->enemies[i].y > table->player_y && table->map[e_spawn_pos_y_map_sub][sprite_x_map] != '1') // up
	// {
	// 	table->enemies[i].y -= 1;
	// 	render_flag = 1;
	// }

/*
	if (table->enemies[i].x == table->player_x)
		table->x_aligned_flag = 1;
	// printf("%d \n", table->x_aligned_flag);
	// printf("2d map down = %c\n", table->map[e_spawn_pos_y_map_add][sprite_x_map]);
	// printf("2d map up = %c\n", table->map[e_spawn_pos_y_map_sub][sprite_x_map]);
	if (table->x_aligned_flag == 1 && table->y_stuck)
	{
		if (table->map[e_spawn_pos_y_map][sprite_x_map_add] == '1')
		{
			table->x_aligned_flag = 0;
			table->y_stuck = 0;
		}
	}
	if (table->x_aligned_flag == 1)
	{
		if (table->map[e_spawn_pos_y_map_add][sprite_x_map] == '1' || table->map[e_spawn_pos_y_map_sub][sprite_x_map] == '1')
		{
			table->y_stuck = 1;
			table->enemies[i].x -= 1;
			render_flag = 1;
		}
		// if (table->map[e_spawn_pos_y_map][sprite_x_map_add] == '1')
		// {
		// 	table->x_aligned_flag = 0;
		// 	table->y_stuck = 0;
		// } 
	}
	*/
	int i = -1;
	int	n_of_deaths = 0;
	while (++i < N_ENEMIES)
	{
		float move_x = 0;
		float move_y = 0;

		render_flag = 1;
		if (table->enemies[i].x < table->player_x)
			move_x = d_t_in_s * 30.0f;
		else if (table->enemies[i].x > table->player_x)
			move_x = -d_t_in_s * 30.0f;
		// else
			// new_x = table->enemies[i].x;
		if (table->enemies[i].y < table->player_y)
			move_y = d_t_in_s * 30.0f;
		else if (table->enemies[i].y> table->player_y)
			move_y = -d_t_in_s * 30.0f;
		// else
			// new_y = table->enemies[i].y;
		
		float new_x = table->enemies[i].x + move_x;
		float new_y = table->enemies[i].y + move_y;

		int r;

		if (new_x != table->enemies[i].x && new_y != table->enemies[i].y)
			r = 25 * sqrt(2);
		else
			r = 25;

		if (!wall_collision_w_circular_bumper(table, new_x, new_y, table->enemies[i].x, table->enemies[i].y, r))
		{
			// printf("normal\n");
			table->enemies[i].x = new_x;
			table->enemies[i].y = new_y;
			render_flag = 1;
		}
		else
		{
				if (!wall_collision_w_circular_bumper(table, table->enemies[i].x, new_y, table->enemies[i].x, table->enemies[i].y, 25))
				{
					// printf("vertical\n");
					table->enemies[i].y = new_y;
					render_flag = 1;
				}
				else if (!wall_collision_w_circular_bumper(table, new_x, table->enemies[i].y, table->enemies[i].x, table->enemies[i].y, 25))
				{
					// printf("horizontal\n");
					table->enemies[i].x = new_x;
					render_flag = 1;
				}
				// else
					// printf("blocked");
		}
		// printf("player x = %f	player y = %f\n", table->player_x, table->player_y);
		// printf("sprite x = %d	sprite y = %d\n\n", table->enemies[i].x, table->enemies[i].y);
		if (table->enemies[i].dead == 1)
			n_of_deaths++;
		if (n_of_deaths == N_ENEMIES)
		{
			init_dynamic_data(table);
			display_gamewon(table);
		}
	}
	if (render_flag == 1)
	{
		draw_minimap(table);
		draw_raycasting(table);
	}
	if (!table->is_attacking)
		insert_fireball(table);
	else
	{
		animate_attack(table);
		if (table->kill)
			kill_sprite(table);
	}
}

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_table	*table;
	//int	avoid_wall_collision;

	table = (t_table *)param;
	
	// ---offset wall collision---
	/*avoid_wall_collision = 20;
	int mpy = table->player_y / T_SIZE;
	int mpx = table->player_x / T_SIZE;
	int mpycw, mpxcw;
	if (table->player_angle >= 0 && table->player_angle < 180)
		mpycw = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpycw = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (table->player_angle >= 270 || table->player_angle < 90)
		mpxcw = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxcw = (table->player_x - avoid_wall_collision) / T_SIZE;
	//printf("mpy = %d\n", mpy);
	//printf("mpx = %d\n", mpx);
	//printf("player x = %f\n", table->player_x);
	//printf("mpyc = %d\n", mpycw);
	//printf("mpxc = %d\n", mpxcw);
	//printf("table->map[%d][%d] %c\n\n", mpycw, mpx, table->map[mpycw][mpx]);
	int mpycs, mpxcs;
	if (table->player_angle > 0 && table->player_angle < 180)
		mpycs = (table->player_y - avoid_wall_collision) / T_SIZE;
	else
		mpycs = (table->player_y + avoid_wall_collision) / T_SIZE;
	if (table->player_angle > 270 || table->player_angle < 90)
		mpxcs = (table->player_x - avoid_wall_collision) / T_SIZE;
	else
		mpxcs = (table->player_x + avoid_wall_collision) / T_SIZE;
	
	int mpycd, mpxcd;
	int pa = table->player_angle + 90;
	if (pa > 359)
			pa -= 360;
	if (pa >= 0 && pa < 180)
		mpycd = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpycd = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (pa >= 270 || pa < 90)
		mpxcd = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxcd = (table->player_x - avoid_wall_collision) / T_SIZE;
	
	int mpyca, mpxca;
	pa = table->player_angle - 90;
	if (pa < 0)
			pa += 360;
	if (pa >= 0 && pa < 180)
		mpyca = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpyca = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (pa >= 270 || pa < 90)
		mpxca = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxca = (table->player_x - avoid_wall_collision) / T_SIZE;

	//int mpy_neg = (table->player_y - avoid_wall_collision) / T_SIZE;
	//int mpy_pos = (table->player_y + avoid_wall_collision) / T_SIZE;
	//int mpx_neg = (table->player_x - avoid_wall_collision) / T_SIZE;
	//int mpx_pos = (table->player_x + avoid_wall_collision) / T_SIZE;
	*/
	// ---offset wall collision---

	// ---circular wall collision---
	
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(table->mlx_start);
		exit (EXIT_SUCCESS);
	}
	if (table->main_menu_on)
		return ;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		table->is_attacking = 1;
		table->kill = 1;
	}
}
