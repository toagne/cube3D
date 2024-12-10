/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:13:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/10 15:10:46 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (angle_to_enemy < 0)
			angle_to_enemy += 360;
		if (angle_to_enemy >= 360)
			angle_to_enemy -= 360;
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
		table->enemies[i].dead = 1;
		table->enemies[i].x = 0;
		table->enemies[i].y = 0;
		table->kill = 0;
	}
}

void	get_time_each_frame(t_table *table)
{
	long	current_time;
	long	delta_time;

	current_time = get_time('b');
	delta_time = current_time - table->last_time;
	table->last_time = current_time;
	table->d_t_in_s = (float)delta_time / 1000000;
}

void	move_player(t_table *table, int *render_flag)
{
	float	new_x;
	float	new_y;

	move_up_down(table, &new_x, &new_y, render_flag);
	move_right_left(table, &new_x, &new_y, render_flag);
	move_visual(table, render_flag);
}

void	set_treshold_for_movement(t_table *table, float *move_x,
	float *move_y, int i)
{
	float	threshold;
	float	speed;
	float	dx;
	float	dy;
	float	distance;

	threshold = 0.1f;
	speed = 10 + (i * 2);
	dx = table->player_x - table->enemies[i].x;
	dy = table->player_y - table->enemies[i].y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > threshold)
	{
		*move_x = (dx / distance) * table->d_t_in_s * speed;
		*move_y = (dy / distance) * table->d_t_in_s * speed;
	}
}

void	check_collisions(t_table *table, t_enemy *sp, float new_x, float new_y)
{
	int	r;

	if (new_x != sp->x && new_y != sp->y)
		r = 15 * sqrt(2);
	else
		r = 15;
	if (!wall_collision_w_circular_bumper(table, new_x, new_y, sp->x, sp->y, r))
	{
		sp->x = new_x;
		sp->y = new_y;
	}
	else
	{
		if (!wall_collision_w_circular_bumper(table, sp->x, new_y,
				sp->x, sp->y, r))
			sp->y = new_y;
		else if (!wall_collision_w_circular_bumper(table, new_x, sp->y,
				sp->x, sp->y, r))
			sp->x = new_x;
	}
}

void	move_sprite(t_table *table, float move_x, float move_y, int i)
{
	float	new_x;
	float	new_y;

	new_x = table->enemies[i].x + move_x;
	new_y = table->enemies[i].y + move_y;
	if ((move_x > 0 && new_x > table->player_x)
		|| (move_x < 0 && new_x < table->player_x))
		new_x = table->player_x;
	if ((move_y > 0 && new_y > table->player_y)
		|| (move_y < 0 && new_y < table->player_y))
		new_y = table->player_y;
	check_collisions(table, &table->enemies[i], new_x, new_y);
}

void	sprite_movements(t_table *table, int *render_flag)
{
	int		i;
	float	move_x;
	float	move_y;
	int		n_of_deaths;

	i = -1;
	n_of_deaths = 0;
	while (++i < N_ENEMIES)
	{
		move_x = 0;
		move_y = 0;
		set_treshold_for_movement(table, &move_x, &move_y, i);
		move_sprite(table, move_x, move_y, i);
		if (table->enemies[i].dead == 1)
			n_of_deaths++;
		if (n_of_deaths == N_ENEMIES)
		{
			init_dynamic_data(table);
			display_gamewon(table);
		}
	}
	*render_flag = 1;
}

void	ft_hook(void *param)
{
	t_table	*table;
	int		render_flag;

	render_flag = 0;
	table = (t_table *)param;
	get_time_each_frame(table);
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
	move_player(table, &render_flag);
	sprite_movements(table, &render_flag);
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
