/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 20:21:10 by giuls            ###   ########.fr       */
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

		draw_line(table->mlx_2D, table->player_x / 4, table->player_y / 4, fx / 4, fy / 4, 0xFFFF00FF);

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
			draw_line(table->mlx_3D, i, 0, i, drawStart, 0xADD8E6FF);
			draw_line(table->mlx_3D, i, drawEnd, i, table->height - 1, 0x8B4513FF);
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
}