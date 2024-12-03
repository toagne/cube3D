/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/12/02 16:16:01 by mpellegr         ###   ########.fr       */
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
                uint32_t color = table->ball_texture.colors[y][frame_x_offset + x];
                
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
	//int	i;
	int base_x;
	int base_y;

	base_x = table->width / 2 - 400 / 2;
	base_y = table->height / 2 + 300;

	int frame_width = 400;   // Width of each frame
    int frame_height = 400;  // Height of each frame

    // Loop through each pixel in the 400x400 frame
    for (int y = 0; y < frame_height; y++)
    {
        for (int x = 0; x < frame_width; x++)
        {
            // Calculate the index of the color in the table.ball_texture_colors array
            // Since the sprite sheet frames are laid out horizontally:
            // - The first frame starts at index 0, the second at index 1, etc.

            // Fetch the color from the sprite sheet array
            uint32_t color = table->ball_texture.colors[y][x];

            // Draw the color to the ball_image buffer at the correct position
            mlx_put_pixel(table->ball_image, base_x + x, base_y + y, color);
        }
    }

	/* i = 0;
	while (i < 30)
	{
		mlx_resize_image(table->p_img[i], table->width / 2, table->height / 2);
		mlx_image_to_window(table->mlx_start, table->p_img[i], base_x, base_y);
		if (i > 0)
		{
			set_image_instance_pos(&table->p_img[i]->instances[0], base_x, base_y - (i * table->height / 100));
			table->p_img[i]->instances[0].enabled = false;
		}
		++i;
	} */
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