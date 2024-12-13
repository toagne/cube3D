/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:50:38 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 08:55:22 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	animate_button(t_button *button)
{
	if (button->status == 1)
	{
		button->white->instances[0].enabled = true;
		button->colored->instances[0].enabled = false;
	}
	else if (button->status == 0)
	{
		button->colored->instances[0].enabled = true;
		button->white->instances[0].enabled = false;
	}
}

void	display_main_menu(t_table *table)
{
	mlx_set_cursor_mode(table->mlx_start, MLX_MOUSE_NORMAL);
	mlx_set_instance_depth(&table->bg_img->instances[0], 13);
	mlx_set_instance_depth(&table->play_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->play_button.colored->instances[0], 15);
	mlx_set_instance_depth(&table->exit_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->exit_button.colored->instances[0], 15);
	mlx_set_instance_depth(&table->controls_button.white->instances[0], 14);
	mlx_set_instance_depth(&table->controls_button.colored->instances[0], 15);
	table->bg_img->instances[0].enabled = true;
	table->play_button.white->instances[0].enabled = true;
	table->exit_button.white->instances[0].enabled = true;
	table->controls_button.white->instances[0].enabled = true;
	table->left_hand->instances[0].enabled = false;
	table->right_hand->instances[0].enabled = false;
	table->ball_image->instances[0].enabled = false;
}

void	undisplay_main_menu(t_table *table)
{
	table->bg_img->instances[0].enabled = false;
	table->play_button.colored->instances[0].enabled = false;
	table->play_button.white->instances[0].enabled = false;
	table->exit_button.white->instances[0].enabled = false;
	table->exit_button.colored->instances[0].enabled = false;
	table->controls_button.white->instances[0].enabled = false;
	table->controls_button.colored->instances[0].enabled = false;
}

static mlx_image_t	*init_background(t_table *table)
{
	mlx_image_t	*img;

	img = load_image(table->mlx_start, "pngs/Background_0.png", table);
	if (!img)
		return (NULL);
	if (!mlx_resize_image(img, table->width, table->height))
		return (NULL);
	if (mlx_image_to_window(table->mlx_start, img, 0, 0) == -1)
		return (NULL);
	return (img);
}

int	init_main_menu(t_table *table)
{
	table->main_menu_on = 1;
	table->bg_img = init_background(table);
	if (!table->bg_img)
	{
		ft_error("Initializing background failed", table);
		return (1);
	}
	if (init_buttons(table))
	{
		ft_error("Initializing button failed", table);
		return (1);
	}
	return (0);
}
