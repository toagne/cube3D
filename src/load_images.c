/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:32:58 by omartela          #+#    #+#             */
/*   Updated: 2024/11/16 17:26:52 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_texture_t *load_texture(char *str)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
	{
		ft_error("Load texture failed");
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
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		ft_error("Load image failed");
		return (NULL);
	}
	return (img);
}
