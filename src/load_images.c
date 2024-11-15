/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:32:58 by omartela          #+#    #+#             */
/*   Updated: 2024/11/15 09:36:06 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_texture_t *load_texture(char *str)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
	{
		error("Load texture failed");
		return (NULL);
	}
	return (texture);
}

mlx_image_t *load_image(mlx_t *mlx, char *str)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = load_texture(str);
	if (!texture)
	{
		img = mlx_texture_to_image(mlx, texture);
		mlx_delete_texture(texture);
	}
	else
		return (NULL);
	if (!img)
	{
		error("Load image failed");
		return (NULL);
	}
	return (img);
}
