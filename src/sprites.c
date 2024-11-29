/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:56:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/29 14:36:01 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	real_check(float p_fov_r, float p_fov_l, float s_r_angle, float s_l_angle)
{
	int	visible;

	visible = 0;
	if (p_fov_r < p_fov_l)
	{
		// FOV does not wrap around 0 degrees
		visible = (s_l_angle >= p_fov_r && s_l_angle <= p_fov_l) ||
				  (s_r_angle >= p_fov_r && s_r_angle <= p_fov_l) ||
				  (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}
	else
	{
		// FOV wraps around 0 degrees
		visible = (s_l_angle >= p_fov_r || s_l_angle <= p_fov_l) ||
				  (s_r_angle >= p_fov_r || s_r_angle <= p_fov_l) ||
				  (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}
	return (visible);
}

int	check_sprite_is_visible(t_table *table, t_enemy sp)
{
	float half_width_angle;
	float s_l_angle;
	float s_r_angle;
	float p_fov_r;
	float p_fov_l;

	sp.angle = atan2(sp.dy, sp.dx) * 180 / PI;
	if (sp.angle < 0)
		sp.angle += 360;
	half_width_angle = atan2(table->sprite_tx.width / 2, sp.dist) * 180 / PI;
	s_l_angle = sp.angle - half_width_angle;
	s_r_angle = sp.angle + half_width_angle;
	if (s_l_angle < 0)
		s_l_angle += 360;
	if (s_r_angle >= 360)
		s_r_angle -= 360;
	p_fov_r = table->player_angle - 30;
	p_fov_l = table->player_angle + 30;
	if (p_fov_r < 0)
		p_fov_r += 360;
	if (p_fov_l >= 360)
		p_fov_l -= 360;
	if (real_check(p_fov_l, p_fov_r, s_r_angle, s_l_angle))
		return (1);
	return (0);
}

void render_sprite(t_table *table, int i)
{
/* 	// Sprite position
	float sprite_x = table->enemies[i].x; // Example sprite position
	float sprite_y = table->enemies[i].y; */
	
	draw_dot(table, table->enemies[i].x / 2, table->enemies[i].y / 2, 2);


	// Compute sprite's position relative to the player
	float sprite_dx = table->enemies[i].x - table->player_x;
	float sprite_dy = table->enemies[i].y - table->player_y;
	float sprite_dist = sqrt(sprite_dx * sprite_dx + sprite_dy * sprite_dy);

	//printf("%f	%f\n", sprite_dx, sprite_dy);
	// Compute angle to the sprite
	float sprite_angle = atan2(sprite_dy, sprite_dx) * 180 / PI;
	//printf("%f	%f\n", table->player_x, table->player_y);
	//printf("sprite angle = %f\n", sprite_angle);
	if (sprite_angle < 0)
		sprite_angle += 360;

	//printf("sprite angle = %f\n", sprite_angle);
	
	float half_width_angle = atan2(table->sprite_tx.width / 2, sprite_dist) * 180 / PI;

	float s_l_angle = sprite_angle - half_width_angle;
	float s_r_angle = sprite_angle + half_width_angle;

	// Normalize angles to [0, 360)
	if (s_l_angle < 0) s_l_angle += 360;
	if (s_r_angle >= 360) s_r_angle -= 360;

	// Calculate angle range within FOV
	float p_fov_r = table->player_angle - 30;
	float p_fov_l = table->player_angle + 30;

	if (p_fov_r < 0) p_fov_r += 360;
	if (p_fov_l >= 360) p_fov_l -= 360;

	bool visible = false;
	if (p_fov_r < p_fov_l)
	{
		// FOV does not wrap around 0 degrees
		visible = (s_l_angle >= p_fov_r && s_l_angle <= p_fov_l) ||
				  (s_r_angle >= p_fov_r && s_r_angle <= p_fov_l) ||
				  (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}
	else
	{
		// FOV wraps around 0 degrees
		visible = (s_l_angle >= p_fov_r || s_l_angle <= p_fov_l) ||
				  (s_r_angle >= p_fov_r || s_r_angle <= p_fov_l) ||
				  (s_l_angle <= p_fov_r && s_r_angle >= p_fov_l);
	}


	
	// Calculate angle difference between sprite and player direction
	float angle_diff = sprite_angle - table->player_angle;
	//printf("%f\n", angle_diff);
	if (angle_diff > 180)
		angle_diff -= 360;
	if (angle_diff < -180)
		angle_diff += 360;

	// Check if sprite is within the FOV
	if (visible)//fabs(angle_diff) < 30)// && fv > sprite_dist)
	{
		// Calculate sprite screen position and size
		float sprite_screen_x = (angle_diff + 30) * table->width / 60;
		//printf("screen x = %f\n", sprite_screen_x);
		float sprite_screen_size = T_SIZE * table->height / sprite_dist;

		int sprite_draw_start_x = sprite_screen_x - sprite_screen_size / 2;
		int sprite_draw_end_x = sprite_screen_x + sprite_screen_size / 2;
		//printf("start x = %d	end x = %d\n", sprite_draw_start_x, sprite_draw_end_x);
		int sprite_draw_start_y = table->height / 2 - sprite_screen_size / 2;
		int sprite_draw_end_y = table->height / 2 + sprite_screen_size / 2;

		// Clipping
		int tex_start_x = 0;

		if (sprite_draw_start_x < 0)
		{
			tex_start_x = -sprite_draw_start_x * table->sprite_tx.width / sprite_screen_size;
			sprite_draw_start_x = 0;
		}
		// add condition if sprite in right side of screen
		if (sprite_draw_end_x >= table->width)
			sprite_draw_end_x = table->width - 1;
		if (sprite_draw_start_y < 0)
			sprite_draw_start_y = 0;
		if (sprite_draw_end_y >= table->height)
			sprite_draw_end_y = table->height - 1;

		//printf("%d	%d\n", sprite_draw_start_x, sprite_draw_end_x);
		//printf("%d	%d\n", sprite_draw_start_y, sprite_draw_end_y);
		
		// Render the sprite column by column
		int x = sprite_draw_start_x - 1;
		while (++x < sprite_draw_end_x)
		{
			float column_angle = table->player_angle + (x - table->width / 2) * (60.0 / table->width);
			if (column_angle < 0) column_angle += 360;
			if (column_angle >= 360) column_angle -= 360;
			float angle = deg_to_rad(column_angle);
			float sx, sy, dx, dy, vv, vh, fv;

			// ----vertical lines----
			vv = 10000;
			if (angle > 3 *PI / 2 || angle < PI / 2)
			{
				sx = (int)(table->player_x / T_SIZE) * T_SIZE + T_SIZE;
				sy = -(table->player_x - sx) * tan(angle) + table->player_y;
				dx = T_SIZE;
				dy = T_SIZE * tan(angle);
			}
			else
			{
				sx = (int)(table->player_x / T_SIZE) * T_SIZE - 0.0001;
				sy = -(table->player_x - sx) * tan(angle) + table->player_y;
				dx = -T_SIZE;
				dy = -T_SIZE * tan(angle);
			}
			//printf("----vertical lines----\nsx = %f\n", sx);
			//printf("sy = %f\n", sy);
			//printf("dx = %f\n", dx);
			//printf("dy = %f\n", dy);
			//printf("angle = %.0f\n", table->player_angle*180/PI);
			int mx, my;
			while (sx > 0 && sy > 0 && sx < T_SIZE * table->columns && sy < T_SIZE * table->rows) //check if need to add more conditins
			{
				mx = sx / T_SIZE;
				my = sy / T_SIZE;
				//printf("mx = %d\n", mx);
				//printf("my = %d\n", my);
				//printf("table->map[%d][%d] = %c\n", mx, my, table->map[mx][my]);
				//printf("%c\n----vertical lines----\n\n", table->map[mp]);
				if (table->map[my][mx] == '1')
					break;
				else
				{
					sx+=dx;
					sy+=dy;
				}
			}
			//printf("sx = %f\n", sx);
			//printf("sy = %f\n", sy);
			vv = sqrt((table->player_x - sx) * (table->player_x -  sx) + (table->player_y - sy) * (table->player_y - sy));
			// vx = sx;
			// vy = sy;
			//printf("\nvertical vector = %f\n", vv);
			// ----horizontals lines----
			vh = 10000;
			if (angle > 0 && angle < PI)
			{
				sy = (int)(table->player_y / T_SIZE) * T_SIZE + T_SIZE;
				sx = -(table->player_y - sy) / tan(angle) + table->player_x;
				dy = T_SIZE;
				dx = T_SIZE / tan(angle);
			}
			else
			{
				sy = (int)(table->player_y / T_SIZE) * T_SIZE - 0.0001;
				sx = -(table->player_y - sy) / tan(angle) + table->player_x;
				dy = -T_SIZE;
				dx = -(T_SIZE / tan(angle));
			}
			//printf("----horizontals lines----\nsx = %f\n", sx);
			//printf("sy = %f\n", sy);
			//printf("dx = %f\n", dx);
			//printf("dy = %f\n", dy);
			//printf("angle = %f\n", table->player_angle);
			//int mx, my, mp;
			while (sx > 0 && sy > 0 && sx < T_SIZE * table->columns && sy < T_SIZE * table->rows) //check if need to add more conditins
			{
				mx = sx / T_SIZE;
				my = sy / T_SIZE;
				//printf("mx = %d\n", mx);
				//printf("my = %d\n", my);
				//printf("table->map[%d][%d] = %c\n", mx, my, table->map[mx][my]);
				//printf("----horizontals lines----\n\n");
				if (table->map[my][mx] == '1')
					break;
				else
				{
					sx+=dx;
					sy+=dy;
				}
			}
			//printf("sy = %f\n", sy);
			//printf("sx = %f\n", sx);
			vh = sqrt((table->player_x - sx) * (table->player_x -  sx) + (table->player_y - sy) * (table->player_y - sy));
			// hx = sx;
			// hy = sy;
				if (vv > vh)
			{
				//printf("vh = %f\n", vh);
				//printf("hx = %f; hy = %f\n", hx, hy);
				// fx  = hx;
				// fy = hy;
				fv = vh;
				//color = 0xFFFF00FF;
				//draw_line(table->mlx_2D, table->player_x, table->player_y, hx, hy, 0xFFFF00FF);
			}
			else
			{
				//printf("vv = %f\n", vv);
				//printf("vx = %f; vy = %f\n\n", vx, vy);
				// fx  = vx;
				// fy = vy;
				fv = vv;
				//color = 0xCCCC00FF;
				//draw_line(table->mlx_2D, table->player_x, table->player_y, vx, vy, 0xFFFF00FF);
			}

			if (sprite_dist > fv)
				continue;

// -----------------------------------------------------------------------------------------
			int tex_x = ((x - sprite_draw_start_x) * table->sprite_tx.width) / sprite_screen_size + tex_start_x;
			int y = sprite_draw_start_y - 1;
				while (++y < sprite_draw_end_y)
				{
					//int tex_x = (x - sprite_draw_start_x) * (table->sprite_tx->width - 1) / sprite_screen_size;
					int tex_y = (y - sprite_draw_start_y) * (table->sprite_tx.height - 1) / sprite_screen_size;

					//printf("%d	%d\n", tex_x, tex_y);

					uint32_t color = table->sprite_tx.colors[tex_y][tex_x];
					if ((color & 0xFF000000) != 0) // Skip transparent pixels
						mlx_put_pixel(table->mlx_3D, x, y, color);
				}
			//}
		}
	}
}

void	order_sprites(t_table *table, t_enemy *sp)
{
	int	i;
	int j;
	t_enemy temp;

	i = -1;
	while (++i < N_ENEMIES)
	{
		sp[i].dx = sp[i].x - table->player_x;
		sp[i].dy = sp[i].y - table->player_y;
		sp[i].dist = sqrt((sp[i].dx * sp[i].dx) + (sp[i].dy * sp[i].dy));
	}
	i = -1;
	while (++i < N_ENEMIES - 1)
	{
		j = -1;
		while (++j < N_ENEMIES - i - 1)
		{
			if (sp[j].dist < sp[j + 1].dist)
			{
				temp = sp[j];
				sp[j] = sp[j + 1];
				sp[j + 1] = temp;
			}
		}
	}
}

void	draw_sprites(t_table *table)
{
	int i;

	order_sprites(table, table->enemies);
	i = -1;
	while (++i < N_ENEMIES)
		if (table->enemies[i].x != 0 && table->enemies[i].y != 0)
			render_sprite(table, i);
}