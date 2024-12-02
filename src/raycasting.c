/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/28 11:19:43 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int find_increment(int i0, int i1)
{
	int i;

	if (i0 < i1)
		i = 1;
	else
		i = -1;
	return (i);
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	sx = find_increment(x0, x1);
	sy = find_increment(y0, y1);
	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;// Stop if we’ve reached the end point
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void render_sprite(t_table *table, int i)
{
	// Sprite position

	float sprite_x = table->enemies[i].x; // Example sprite position
	float sprite_y = table->enemies[i].y;

	//draw_circle(table->mlx_2D, sprite_x / 2, sprite_y / 2, 25 / 2, 0x00FF00FF);

	int y1 = sprite_y / 2 - 2;
	while (y1++ < sprite_y / 2 + 2)
	{
		int x1 = sprite_x / 2 - 2;
		while (x1++ < sprite_x / 2 + 2)
			mlx_put_pixel(table->mlx_2D, x1, y1, 0xFF0000FF);
	}

	// Compute sprite's position relative to the player
	float sprite_dx = sprite_x - table->player_x;
	float sprite_dy = sprite_y - table->player_y;
	float sprite_dist = sqrt(sprite_dx * sprite_dx + sprite_dy * sprite_dy);

	//printf("%f	%f\n", sprite_dx, sprite_dy);
	// Compute angle to the sprite
	float sprite_angle = atan2(sprite_dy, sprite_dx) * 180 / PI;
	//printf("%f	%f\n", table->player_x, table->player_y);
	//printf("sprite angle = %f\n", sprite_angle);
	if (sprite_angle < 0)
		sprite_angle += 360;

	//printf("sprite angle = %f\n", sprite_angle);
	
	float half_width_angle = atan2(table->enemy_texture->width / 2, sprite_dist) * 180 / PI;

	float sprite_left_angle = sprite_angle - half_width_angle;
	float sprite_right_angle = sprite_angle + half_width_angle;

	// Normalize angles to [0, 360)
	if (sprite_left_angle < 0) sprite_left_angle += 360;
	if (sprite_right_angle >= 360) sprite_right_angle -= 360;

	// Calculate angle range within FOV
	float player_fov_left = table->player_angle - 30;
	float player_fov_right = table->player_angle + 30;

	if (player_fov_left < 0) player_fov_left += 360;
	if (player_fov_right >= 360) player_fov_right -= 360;

	bool visible = false;
	if (player_fov_left < player_fov_right)
	{
		// FOV does not wrap around 0 degrees
		visible = (sprite_left_angle >= player_fov_left && sprite_left_angle <= player_fov_right) ||
				  (sprite_right_angle >= player_fov_left && sprite_right_angle <= player_fov_right) ||
				  (sprite_left_angle <= player_fov_left && sprite_right_angle >= player_fov_right);
	}
	else
	{
		// FOV wraps around 0 degrees
		visible = (sprite_left_angle >= player_fov_left || sprite_left_angle <= player_fov_right) ||
				  (sprite_right_angle >= player_fov_left || sprite_right_angle <= player_fov_right) ||
				  (sprite_left_angle <= player_fov_left && sprite_right_angle >= player_fov_right);
	}
/*
	int ssx = enemy_texture->width / 2 * -1;
	int esx = enemy_texture->width / 2;
	int nssx = ssx * cos(deg_to_rad(sprite_angle - 270)) - 0 * (sin(deg_to_rad(sprite_angle - 270)));
	int nssy = 0 * cos(deg_to_rad(sprite_angle - 270)) + ssx * (sin(deg_to_rad(sprite_angle - 270)));
	printf("%d	%d\n", nssx, nssy);
	nssx += sprite_x;
	nssy += sprite_y;
	printf("%d	%f\n", ssx, sprite_y);
	printf("%d	%d\n", nssx, nssy);
	int nesx = esx * cos(deg_to_rad(sprite_angle - 270)) - 0 * (sin(deg_to_rad(sprite_angle - 270)));
	int nesy = 0 * cos(deg_to_rad(sprite_angle - 270)) + esx * (sin(deg_to_rad(sprite_angle - 270)));
	nesx += sprite_x;
	nesy += sprite_y;
	draw_line(table->mlx_2D, table->player_x / 2, table->player_y / 2, sprite_x / 2, sprite_y / 2, 0x00FF00FF);
	draw_line(table->mlx_2D, table->player_x / 2, table->player_y / 2, nssx / 2, nssy / 2, 0x00FF00FF);
	draw_line(table->mlx_2D, table->player_x / 2, table->player_y / 2, nesx / 2, nesy / 2, 0x00FF00FF);
*/

	
	// Calculate angle difference between sprite and player direction
	float angle_diff = sprite_angle - table->player_angle;
	//printf("%f\n", angle_diff);
	if (angle_diff > 180)
		angle_diff -= 360;
	if (angle_diff < -180)
		angle_diff += 360;
	//printf("original angle diff = %f\n", angle_diff);
	/*
	if (angle_diff < 0)
	{
		sprite_dx += nesx - table->player_x;
		sprite_dy += nesy - table->player_y;
	}
	else
	{
		sprite_dx -= nssx - table->player_x;
		sprite_dy -= nssy - table->player_y;
	}
	float edge_sprite_angle = atan2(sprite_dy, sprite_dx) * 180 / PI;
	if (edge_sprite_angle < 0)
		edge_sprite_angle += 360;
	printf("%f	%f\n", sprite_dx, sprite_dy);
	printf("sprite edge angle = %f\n", edge_sprite_angle);
	float edge_angle_diff = edge_sprite_angle - table->player_angle;
	if (edge_angle_diff > 180)
		edge_angle_diff -= 360;
	if (edge_angle_diff < -180)
		edge_angle_diff += 360;
	printf("sprite edge angle diff = %f\n", edge_angle_diff);

	// -------------------------------------------------------
	int first_non_transparent_col = -1; // Initialize to an invalid index
	int last_non_transparent_col = -1; // Initialize to an invalid index

	// Iterate through each column
	for (int tx_col = 0; tx_col < (int)enemy_texture->width; ++tx_col)
	{
		bool is_non_transparent = false;

		// Check if the column has at least one non-transparent pixel
		for (int tx_row = 0; tx_row < (int)enemy_texture->height; ++tx_row)
		{
			if (enemy_texture_colors[tx_row][tx_col] != 0x00000000) // Non-transparent pixel found
			{
				is_non_transparent = true;
				break; // No need to check further rows in this column
			}
		}

		// Update the bounds of non-transparent columns
		if (is_non_transparent)
		{
			if (first_non_transparent_col == -1) // First non-transparent column
				first_non_transparent_col = tx_col;

			last_non_transparent_col = tx_col; // Update last non-transparent column
		}
	}

	// Calculate the real width
	int real_width = 0;
	if (first_non_transparent_col != -1 && last_non_transparent_col != -1)
	{
		real_width = last_non_transparent_col - first_non_transparent_col + 1;
	}

	// Output the result
	//printf("first_non_transparent_col = %d\n", first_non_transparent_col);
	//printf("last_non_transparent_col = %d\n", last_non_transparent_col);
	//printf("Real Width of the Texture: %d\n", real_width);
	// -------------------------------------------------------
	*/
	//printf("%09X\n", enemy_texture_colors[20][20]);
	
	

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
			tex_start_x = -sprite_draw_start_x * table->enemy_texture->width / sprite_screen_size;
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
			int tex_x = ((x - sprite_draw_start_x) * table->enemy_texture->width) / sprite_screen_size + tex_start_x;
			int y = sprite_draw_start_y - 1;
				while (++y < sprite_draw_end_y)
				{
					//int tex_x = (x - sprite_draw_start_x) * (enemy_texture->width - 1) / sprite_screen_size;
					int tex_y = (y - sprite_draw_start_y) * (table->enemy_texture->height - 1) / sprite_screen_size;

					//printf("%d	%d\n", tex_x, tex_y);

					uint32_t color = table->enemy_texture_colors[tex_y][tex_x];
					if ((color & 0xFF000000) != 0) // Skip transparent pixels
						mlx_put_pixel(table->mlx_3D, x, y, color);
				}
			//}
		}
	}
}

// void	move_enemy(void *param)
// {
// 	t_table	*table;

// 	table = (t_table *)param;
// 	//printf("sprite x = %d\n", table->sprite_x);
// 	//printf("player x = %f\n", table->player_x);
// 	while (table->sprite_x < table->player_x)
// 		table->sprite_x += 5;
// 	render_sprite(table);
// }

void	order_sprites(t_table *table)
{
	int	dx;
	int dy;
	int	i;
	int j;
	t_enemy temp;

	i = -1;
	while (++i < N_ENEMIES)
	{
		dx = table->enemies[i].x - table->player_x;
		dy = table->enemies[i].x - table->player_x;
		table->enemies[i].dist = sqrt((dx * dx) + (dy * dy));
	}
	i = -1;
	while (++i < N_ENEMIES - 1)
	{
		j = -1;
		while (++j < N_ENEMIES - i - 1)
		{
			if (table->enemies[j].dist < table->enemies[j + 1].dist)
			{
				temp = table->enemies[j];
				table->enemies[j] = table->enemies[j + 1];
				table->enemies[j + 1] = temp;
			}
		}
	}
}

void	draw_raycasting(t_table *table)
{
	float pa = table->player_angle - 30;
	int n_of_rays = table->width / 2;
	//printf("\nplayer angle = %f\n", table->player_angle);
	//printf("player angle - 30 = %f\n", pa);
	int r = -1;
	while (++r < n_of_rays)
	{
		if (pa > 359)
			pa -= 360;
		if (pa < 0)
			pa += 360;
		float angle = deg_to_rad(pa);
		float sx, sy, dx, dy, vv, vh, hx, hy, vx, vy, fx, fy, fv;
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
		vx = sx;
		vy = sy;
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
		hx = sx;
		hy = sy;
		//printf("horizontal vector = %f\n", vh);
		//uint32_t color;
		if (vv > vh)
		{
			//printf("vh = %f\n", vh);
			//printf("hx = %f; hy = %f\n", hx, hy);
			fx  = hx;
			fy = hy;
			fv = vh;
			//color = 0xFFFF00FF;
			//draw_line(table->mlx_2D, table->player_x, table->player_y, hx, hy, 0xFFFF00FF);
		}
		else
		{
			//printf("vv = %f\n", vv);
			//printf("vx = %f; vy = %f\n\n", vx, vy);
			fx  = vx;
			fy = vy;
			fv = vv;
			//color = 0xCCCC00FF;
			//draw_line(table->mlx_2D, table->player_x, table->player_y, vx, vy, 0xFFFF00FF);
		}
		//printf("mx = %d\n", mx);
		//printf("my = %d\n", my);
		//printf("mp = %d\n", mp);
		//printf("%c\n", table->map[mp]);
		
		//printf("ray %d, final vector = %f\n", r, fv);

		//printf("fx = %f	fy = %f\n", fx, fy);
		draw_line(table->mlx_2D, table->player_x / 2, table->player_y / 2, fx / 2, fy / 2, 0xFFFF00FF);

		// comment this out
		int minimap_size = fmin(table->width / 4, table->height / 4);
		// printf("minimap size = %d\n", minimap_size);
		int vpx0 = (table->player_x - (minimap_size / 2));
		int vpy0 = (table->player_y - (minimap_size / 2));
		int vpx1 = vpx0 + minimap_size;
		int vpy1 = vpy0 + minimap_size;
		// printf("fx = %f	fy = %f\n", fx, fy);
		// printf("vpx0 = %d	vpx1 = %d\n", vpx0, vpx1);
		// printf("vpy0 = %d	vpy1 = %d\n", vpy0, vpy1);
		int rx1 = fx;
		int ry1 = fy;
		if (vpx0 > fx && (vpx0 - fx) > (vpy0 - fy) && (vpx0 - fx) > (fy - vpy1))
		{
			rx1 = vpx0;
			ry1 = -(table->player_x - rx1) * tan(angle) + table->player_y;
		}
		if (vpx1 < fx && (fx - vpx1) > (fy - vpy1) && (fx - vpx1) > (vpy0 - fy))
		{
			rx1 = vpx1;
			if (pa == 0 || pa == 360)
				ry1 = table->player_y;
			else
				ry1 = -(table->player_x - rx1) * tan(angle) + table->player_y;
		}
		if (vpy0 > fy && (vpy0 - fy) > (vpx0 - fx) && (vpy0 - fy) > (fx - vpx1))
		{
			ry1 = vpy0;
			if (pa == 270)
				rx1 = table->player_x;
			else
				rx1 = -(table->player_y - ry1) / tan(angle) + table->player_x;
		}
		if (vpy1 < fy && (fy - vpy1) > (fx - vpx1) && (fy - vpy1) > (vpx0 - fx))
		{
			ry1 = vpy1;
			rx1 = -(table->player_y - ry1) / tan(angle) + table->player_x;
		}
		rx1 -= vpx0;
		ry1 -= vpy0;
		if (rx1 == minimap_size)
			rx1 -= 1;
		if (ry1 == minimap_size)
			ry1 -= 1;	
		// printf("player x%f	player y%f\n", table->player_x, table->player_y);
		// printf("rx1 = %d	ry1 = %d\n", rx1, ry1);
		// printf("angle = %f\n", pa);
		
		//draw_line(table->mlx_2D, table->player_x - vpx0, table->player_y - vpy0, rx1, ry1, 0xFFFF00FF);

		uint32_t	**tx_color;

		tx_color = NULL;

		int tile_x, tile_y;
		tile_x = (int)(fx / T_SIZE) * T_SIZE;
		tile_y = (int)(fy / T_SIZE) * T_SIZE;
		//printf("tile_x = %d	tile_y = %d\n", tile_x, tile_y);
		//printf("fx = %f	fy = %f\n", fx, fy);

		//printf("int fy = %d\n", (int)fy);
		//printf("%d\n", tile_y + T_SIZE - 1);

		//printf("int fx = %d\n", (int)fx);
		//printf("%d\n", tile_x + T_SIZE);

		float ndx = fx - tile_x;
		float ndy = fy - tile_y;

		//printf("ndx = %f	ndy = %f\n", ndx, ndy);

		if (ndy > ndx && ndy > (T_SIZE - ndx))
			tx_color = table->no_texture_colors; // N
		else if (ndy < ndx && ndy < (T_SIZE - ndx))
			tx_color = table->so_texture_colors; // S
		else if (ndx <= ndy && ndx <= (T_SIZE - ndy))
			tx_color = table->ws_texture_colors; // W
		else
			tx_color = table->es_texture_colors; // E

		int ca=(table->player_angle - pa);
		if (ca > 359)
			ca -= 360;
		if (ca < 0)
			ca += 360;
		fv=fv*cos(deg_to_rad(ca));

		//printf("\nvector %d angle = %f\n", r, pa);
		//printf("vextor %d = %f\n", r, fv);
		int wall_h = T_SIZE * table->height / fv;
		float tx_vertical_step = (float)table->es_texture->height / wall_h;
		float tx_v_offset = 0;
		//printf("wall h %d = %d\n", r, wall_h);
		if (wall_h > table->height)
		{
			tx_v_offset = (wall_h - table->height) / 2;
			wall_h = table->height;
		}
		int drawStart = table->height / 2 - wall_h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = wall_h / 2 + table->height / 2;
		if(drawEnd >= table->height)
			drawEnd = table->height - 1;
		//printf("wall_h = %d\n", wall_h);
		//printf("render_x = %d\n", render_x);
		//printf("draw start = %d\n", drawStart);
		//printf("draw end = %d\n", drawEnd);
		
		int scaled_x_start = r * (table->width / n_of_rays);
		int scaled_x_end = (r + 1) * (table->width / n_of_rays) - 1;
		int i = scaled_x_start;
		//printf("scaled x end = %d\n", scaled_x_end);

		//float tx_vertical_step = (float)table->es_texture->height / wall_h;
		//float tx_horizntal_step = (float)table->es_texture->width / (scaled_x_end - scaled_x_start + 1);
		//printf("h step = %f\n", tx_horizntal_step);
		//printf("vertical step = %f\n", tx_vertical_step);
		//float ty = tx_v_offset * tx_vertical_step;
		float ty = tx_v_offset * tx_vertical_step;

		//if (tx_v_offset > 0)
		//	printf("ray n = %d	wall h = %d	offset = %f	vertical step = %f	ty = %f\n", r, (int)(T_SIZE * 800 / fv), tx_v_offset, tx_vertical_step, ty);

		float tx;
		if (vv > vh)
		{
			tx = ((int)fx % T_SIZE) * table->es_texture->width / T_SIZE;
			if (table->player_angle < 180)
			{
				if (tx == 0)
					tx = table->es_texture->width;
				tx = table->es_texture->width - tx;
			}
		}
		else
		{
			tx = ((int)fy % T_SIZE) * table->es_texture->width / T_SIZE;
			if (table->player_angle > 90 && table->player_angle < 270)
			{
				if (tx == 0)
					tx = table->es_texture->width;
				tx = table->es_texture->width - tx;
			}
		}
			
		//printf("tx x hitting point = %f\n", tx);
		
		//float tx = ((int)fv % T_SIZE) * table->es_texture->width / T_SIZE;
		
		//printf("tx = %f\n", tx);

		// Draw the wider vertical slice across the scaled width range
		while (i <= scaled_x_end)
		{
			draw_line(table->mlx_3D, i, 0, i, drawStart, get_rgba(table->c_color[0],table->c_color[1],table->c_color[2], 255));
			draw_line(table->mlx_3D, i, drawEnd, i, table->height - 1, get_rgba(table->f_color[0],table->f_color[1],table->f_color[2], 255));
			//draw_line(table->mlx_3D, i, drawStart, i, drawEnd, color);
			int a = drawStart;
			ty = tx_v_offset * tx_vertical_step;
			while (a <= drawEnd)
			{
				int tex_x = (int)tx;
				int tex_y = (int)ty;
				if (tex_y >= (int)table->es_texture->height)
					tex_y = table->es_texture->height - 1;
				//printf("%08X\n", table->no_texture_colors[tex_y][tex_x]);
				//printf("ty_int = %d\n", tex_y);
				//printf("%d x %d\n", i, a);
				//printf("colour [%d][%d] = %08X\n", tex_y, tex_x, table->es_texture_colors[tex_y][tex_x]);
				//printf("%d	%d\n", tex_x, tex_y);
				mlx_put_pixel(table->mlx_3D, i, a, tx_color[tex_y][tex_x]);
				//if (tx_v_offset > 0)
				//	mlx_put_pixel(table->mlx_3D, i, a, 0x000000FF);
				ty += tx_vertical_step;
				a++;
			}
			//tx += tx_horizntal_step;
			i++;
		}
		pa = pa + ((float)60 / n_of_rays);
	}
	order_sprites(table);
	int i = -1;
	while (++i < N_ENEMIES)
		if (table->enemies[i].x != 0 && table->enemies[i].y != 0)
			render_sprite(table, i);
	//mlx_image_to_window(table->mlx_start, table->mlx_3D, 0, 0);
	//mlx_image_to_window(table->mlx_start, table->mlx_2D, 0, 0);
}