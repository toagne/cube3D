/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/11/22 16:10:10 by mpellegr         ###   ########.fr       */
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
    int frame_width = 400;   // Width of each frame (400px)
    int frame_height = 400;  // Height of each frame (400px)
	int	y_offset;
    int base_x = table->width / 2 - 400 / 2;
	int base_y = table->height / 2 - 400 / 2;      // The y-coordinate where the animation will be drawn on the screen

    if (table->frame_counter)
    {
        // Draw the new frame using put_pixel (get the current frame from the sprite sheet)
        int frame_x_offset = table->p_anim_index * frame_width;  // Each frame is 400px wide

		y_offset = table->height / 2 - frame_height / 2 - (table->p_anim_index * 3);
        for (int y = 0; y < frame_height - 1; y++)
        {
            for (int x = 0; x < frame_width - 1; x++)
            {
                // Access the color from the sprite sheet (2D array with sprite data)
                uint32_t color = table->ball_texture_colors[y][frame_x_offset + x];
                
                // Draw the current frame pixel to the screen at the right position
                mlx_put_pixel(table->ball_image, base_x + x, base_y + y + y_offset, color);
            }
        }

        // Update the animation index
        if (table->p_anim_index == 29)  // If the last frame (frame 29), reset animation
        {
            table->is_attacking = 0;
            table->p_anim_index = 0;
			//set_image_instance_pos(&table->ball_image->instances[0], base_x, base_y);
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
	float ratio = (float)table->ball_texture->width / 30 / table->ball_texture->height;
	if (frame_width / ratio > frame_height) {
        frame_width = (int)(frame_height * ratio);
    } else {
        frame_height = (int)(frame_width / ratio);
    }
	base_x = table->width / 2 - frame_width / 2;
	base_y = table->height - frame_height;
	float sw = (float)400 / frame_width;
	float sh = (float)table->ball_texture->height / frame_height;
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
            uint32_t color = table->ball_texture_colors[tex_y][tex_x];
            mlx_put_pixel(table->ball_image, base_x + x, base_y + y, color);
			tx += sw;
		}
		ty += sh;
    }
	return (0);
}

int	insert_player_texture(t_table *table)
{
	insert_fireball(table);
	mlx_resize_image(table->left_hand, table->width / 10, table->height / 6);
	mlx_resize_image(table->right_hand, table->width / 10, table->height / 6);
	mlx_image_to_window(table->mlx_start, table->left_hand, table->width / 2 - 200, table->height - 150);
	mlx_image_to_window(table->mlx_start , table->right_hand, table->width / 2 + 50, table->height - 150);
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
	/* mlx_resize_image(table->p_img[table->p_anim_index], 300, 300);
	index = mlx_image_to_window(table->mlx_start, table->p_img[0], table->width / 2 - 150, table->height - 300);
	mlx_set_instance_depth(&table->p_img[table->p_anim_index]->instances[index], 4); */
	return (0);
}