/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:13:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 16:18:17 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_time_each_frame(t_table *table)
{
	long	current_time;
	long	delta_time;

	current_time = get_time('b');
	delta_time = current_time - table->last_time;
	table->last_time = current_time;
	table->d_t_in_s = (float)delta_time / 1000000;
}

void	move_player(t_table *table)
{
	t_collision	p_coll;

	p_coll.x0 = table->player_x;
	p_coll.y0 = table->player_y;
	p_coll.r = 10;
	move_up_down(table, &p_coll);
	move_right_left(table, &p_coll);
	move_visual(table);
}

void	move_sprite(t_table *table, float move_x, float move_y, int i)
{
	t_collision	s_coll;

	s_coll.x0 = table->enemies[i].x;
	s_coll.y0 = table->enemies[i].y;
	s_coll.x1 = table->enemies[i].x + move_x;
	s_coll.y1 = table->enemies[i].y + move_y;
	if ((move_x > 0 && s_coll.x1 > table->player_x)
		|| (move_x < 0 && s_coll.x1 < table->player_x))
		s_coll.x1 = table->player_x;
	if ((move_y > 0 && s_coll.y1 > table->player_y)
		|| (move_y < 0 && s_coll.y1 < table->player_y))
		s_coll.y1 = table->player_y;
	check_collisions(table, &table->enemies[i], &s_coll);
}

void	sprite_movements(t_table *table)
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
}

void	ft_hook(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	get_time_each_frame(table);
	if (table->gameover_on == 1)
		run_gamestate_img(table, table->gameoverimg);
	else if (table->gamewon_on == 1)
		run_gamestate_img(table, table->gamewonimg);
	if (table->main_menu_on || table->gameover_on || table->gamewon_on)
		return ;
	table->frame_counter += 1;
	move_player(table);
	sprite_movements(table);
	draw_minimap(table);
	draw_raycasting(table);
	if (!table->is_attacking)
		insert_fireball(table);
	else
	{
		animate_attack(table, &table->fireball);
		if (table->kill)
			kill_sprite(table);
	}
}
