/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:32:58 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 11:50:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static mlx_texture_t	*load_texture(char *str, t_table *table)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
	{
		ft_error("Load texture failed", table);
		return (NULL);
	}
	return (texture);
}

mlx_image_t	*load_image(mlx_t *mlx, char *str, t_table *table)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = load_texture(str, table);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		ft_error("Load image failed", table);
		return (NULL);
	}
	return (img);
}

static void	alloc_colors_memory(t_table *t, uint32_t ***tx_colors,
	mlx_texture_t *tx)
{
	uint32_t	i;

	*tx_colors = (uint32_t **)ft_calloc((tx->height + 1), sizeof(uint32_t *));
	if (!(*tx_colors))
	{
		free_all(t);
		ft_error("Memory allocation failed for rows", t);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < tx->height)
	{
		(*tx_colors)[i] = (uint32_t *)ft_calloc((tx->width + 1),
				sizeof(uint32_t));
		if (!(*tx_colors)[i])
		{
			while (--i)
				free((*tx_colors)[i]);
			free(*tx_colors);
			*tx_colors = NULL;
			free_all(t);
			ft_error("Memory allocation failed for columns", t);
			exit(EXIT_FAILURE);
		}
	}
}

static void	populate_colors_array(uint32_t ***tx_colors, mlx_texture_t	*tx)
{
	uint32_t	i;
	uint32_t	x;
	uint32_t	y;

	i = 0;
	y = -1;
	while (++y < tx->height)
	{
		x = -1;
		while (++x < tx->width)
		{
			(*tx_colors)[y][x] = get_rgba(tx->pixels[i],
					tx->pixels[i + 1], tx->pixels[i + 2], tx->pixels[i + 3]);
			i += 4;
		}
	}
}

void	convert_tx(t_table *t, t_texture *my_tx,
	uint32_t ***tx_colors, char *str)
{
	mlx_texture_t	*tx;

	tx = load_texture(str, t);
	if (!tx)
	{
		free_all(t);
		ft_error("Load texture failed", t);
		exit(EXIT_FAILURE);
	}
	alloc_colors_memory(t, tx_colors, tx);
	populate_colors_array(tx_colors, tx);
	my_tx->height = tx->height;
	my_tx->width = tx->width;
	mlx_delete_texture(tx);
}
