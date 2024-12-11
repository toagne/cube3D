/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/12/11 16:21:48 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_animation(t_table *t, t_fireball *f, int x, int y)
{
	float		tx;
	float		ty;
	int			tex_x;
	int			tex_y;

	ty = 0;
	y = -1;
	while (++y < f->frame_height)
	{
		tx = 0;
		x = -1;
		while (++x < f->frame_width)
		{
			tex_x = (int)(f->x_offset + tx);
			tex_y = (int)ty;
			mlx_put_pixel(t->ball_image, f->base_x + x,
				f->base_y + y + f->y_offset, 0x00000000);
			if (t->ball_texture.colors[tex_y][tex_x] != 0x000000FF)
				mlx_put_pixel(t->ball_image, f->base_x + x,
					f->base_y + y + f->y_offset,
					t->ball_texture.colors[tex_y][tex_x]);
			tx += f->step_w;
		}
		ty += f->step_h;
	}
}

void	animate_attack(t_table *t, t_fireball *f)
{
	int		y;
	int		x;

	x = 0;
	y = 0;
	if (t->frame_counter)
	{
		f->x_offset = t->p_anim_index * 400 * 6 + t->p_anim_index;
		f->y_offset = (t->height / 2 - f->base_y) / 5 * t->p_anim_index;
		draw_animation(t, f, x, y);
		if (t->p_anim_index == 4)
		{
			t->is_attacking = 0;
			t->p_anim_index = 0;
			y = t->height / 2 - 1;
			while (++y < t->height - f->frame_height)
			{
				x = -1;
				while (++x < f->frame_width)
					mlx_put_pixel(t->ball_image, f->base_x + x, y, 0x00000000);
			}
		}
		else
			t->p_anim_index += 1;
	}
}

void	draw_scaled_fireball(t_fireball	fireball, float tx, float ty,
	t_table *table)
{
	int			y;
	int			x;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	ty = 0.0;
	y = -1;
	while (++y < fireball.frame_height)
	{
		tx = 0.0;
		x = -1;
		while (++x < fireball.frame_width)
		{
			tex_x = (int)tx;
			tex_y = (int)ty;
			color = table->ball_texture.colors[tex_y][tex_x];
			mlx_put_pixel(table->ball_image, fireball.base_x + x,
				fireball.base_y + y, color);
			tx += fireball.step_w;
		}
		ty += fireball.step_h;
	}
}

void	insert_fireball(t_table *t)
{
	float		ratio;
	float		tx;
	float		ty;

	t->fireball.frame_width = t->width * 0.3;
	t->fireball.frame_height = t->height * 0.3;
	ratio = (float)t->ball_texture.width / 30 / t->ball_texture.height;
	if (t->fireball.frame_width / ratio > t->fireball.frame_height)
		t->fireball.frame_width = (int)(t->fireball.frame_height * ratio);
	else
		t->fireball.frame_height = (int)(t->fireball.frame_width / ratio);
	t->fireball.base_x = t->width / 2 - t->fireball.frame_width / 2;
	t->fireball.base_y = t->height - t->fireball.frame_height;
	t->fireball.step_w = (float)400 / t->fireball.frame_width;
	t->fireball.step_h = (float)t->ball_texture.height
		/ t->fireball.frame_height;
	tx = 0.0;
	ty = 0.0;
	draw_scaled_fireball(t->fireball, tx, ty, t);
}

int	insert_player_texture(t_table *table)
{
	int	hand_w;
	int	hand_h;

	hand_w = table->width / 10;
	hand_h = table->height / 6;
	insert_fireball(table);
	mlx_resize_image(table->left_hand, hand_w, hand_h);
	mlx_resize_image(table->right_hand, hand_w, hand_h);
	mlx_image_to_window(table->mlx_start, table->left_hand,
		table->width / 2 - hand_w, table->height - hand_h);
	mlx_image_to_window(table->mlx_start, table->right_hand,
		table->width / 2, table->height - hand_h);
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
	return (0);
}
