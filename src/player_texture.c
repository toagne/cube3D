/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/12/07 11:04:39 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* int animate_attack(t_table *table)
{
	if (table->frame_counter)
	{
		if (table->p_anim_index > 0)
			table->p_img[table->p_anim_index - 1]->instances[0].enabled = false;
		else if (table->p_anim_index == 0 && table->is_attacking)
			table->p_img[29]->instances[0].enabled = false;

		if (table->p_anim_index == 29)
		{
			table->p_img[0]->instances[0].enabled = true;
			table->is_attacking = 0;
			table->p_anim_index = 0;
		}
		else
		{
			table->p_img[table->p_anim_index]->instances[0].enabled = true;
			table->p_anim_index += 1;
		}
	}
	return (0);
} */

int animate_attack(t_table *table)
{
	// Compute frame size based on window size
	int frame_width = table->width * 0.3;
	int frame_height = table->height * 0.3;
	float ratio = (float)table->ball_texture.width / 30 / table->ball_texture.height;
	int	y_offset;
	if (frame_width / ratio > frame_height)
		frame_width = (int)(frame_height * ratio);
	else
		frame_height = (int)(frame_width / ratio);

	// Base coordinates for animation
	int base_x = table->width / 2 - frame_width / 2;
	int base_y = table->height - frame_height;

	// Scaling factors
	float sw = (float)400 / frame_width; // One frame is 400px wide
	float sh = (float)table->ball_texture.height / frame_height;

	// Draw current animation frame
	float tx, ty = 0.0f;
	if (table->frame_counter)
	{
		int frame_x_offset = table->p_anim_index * 400 * 6 + table->p_anim_index; // Offset for the current frame
		y_offset = (table->height / 2 - base_y) / 5 * table->p_anim_index;
		for (int y = 0; y < frame_height; y++)
		{
			tx = 0.0f;
			for (int x = 0; x < frame_width; x++)
			{
				int tex_x = (int)(frame_x_offset + tx);
				int tex_y = (int)ty;
				
				mlx_put_pixel(table->ball_image, base_x + x, base_y + y + y_offset, 0x00000000);

				uint32_t color = table->ball_texture.colors[tex_y][tex_x];

				// Skip transparent pixels (assuming 0x00000000 is transparent)
				if ((color & 0xFF000000) != 0)
				{
					mlx_put_pixel(table->ball_image, base_x + x, base_y + y + y_offset, color);
				}
				tx += sw;
			}
			ty += sh;
		}
		// Update the animation index
		if (table->p_anim_index == 4) // If the last frame
		{
			table->is_attacking = 0;
			table->p_anim_index = 0;
			int y = table->height / 2 - 1;
			while (++y < table->height - frame_height)
			{
				int x = -1;
				while (++x < frame_width)
				{
					// printf("base_x = %d	base_y = %d\n", base_x, base_y);
					mlx_put_pixel(table->ball_image, base_x + x, y, 0x00000000);
				}
			}
		}
		else
		{
			table->p_anim_index += 1;
		}
	}

	return (0);
}


void	set_image_instance_pos(mlx_instance_t *instance, int x, int y)
{
	instance->x = x;
	instance->y = y;
}

int	insert_fireball(t_table *table)
{
	int base_x;
	int base_y;

	int frame_width = table->width * 0.3;
	int frame_height = table->height * 0.3;
	float ratio = (float)table->ball_texture.width / 30 / table->ball_texture.height;
	if (frame_width / ratio > frame_height) 
	{
		frame_width = (int)(frame_height * ratio);
	} else 
	{
		frame_height = (int)(frame_width / ratio);
	}
	base_x = table->width / 2 - frame_width / 2;
	base_y = table->height - frame_height;
	float sw = (float)400 / frame_width;
	float sh = (float)table->ball_texture.height / frame_height;
	float	tx;
	float	ty;
	ty = 0;
	for (int y = 0; y < frame_height; y++)
	{
		tx = 0;
		for (int x = 0; x < frame_width; x++)
		{
			int tex_x = (int)tx;
			int tex_y = (int)ty;
			uint32_t color = table->ball_texture.colors[tex_y][tex_x];
			mlx_put_pixel(table->ball_image, base_x + x, base_y + y, color);
			tx += sw;
		}
		ty += sh;
	}
	return (0);
}

int	insert_player_texture(t_table *table)
{
	int	hand_w;
	int hand_h;

	hand_w = table->width / 10;
	hand_h = table->height / 6;
	insert_fireball(table);
	mlx_resize_image(table->left_hand, hand_w, hand_h);
	mlx_resize_image(table->right_hand, hand_w, hand_h);
	mlx_image_to_window(table->mlx_start, table->left_hand, table->width / 2 - hand_w, table->height - hand_h);
	mlx_image_to_window(table->mlx_start, table->right_hand, table->width / 2, table->height - hand_h);
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
	/* mlx_resize_image(table->p_img[table->p_anim_index], 300, 300);
	index = mlx_image_to_window(table->mlx_start, table->p_img[0], table->width / 2 - 150, table->height - 300);
	mlx_set_instance_depth(&table->p_img[table->p_anim_index]->instances[index], 4); */
	return (0);
}