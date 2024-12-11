/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:41:29 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/11 17:00:58 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

void	get_monitor_size(int *width, int *height)
{
	mlx_t	*temp;
	int32_t	w;
	int32_t	h;

	temp = mlx_init(1, 1, "", false);
	if (!temp)
	{
		// free
		exit(EXIT_FAILURE);
	}
	mlx_get_monitor_size(0, &w, &h);
	mlx_terminate(temp);
	*width = w / 1.5;
	*height = h / 1.5;
}

float	deg_to_rad(float deg)
{
	return ((float)deg / 180 * PI);
}

int	my_rand(t_table *table)
{
	long	lcg_a;
	long	lcg_c;
	long	lcg_m;

	lcg_a = 1103515245;
	lcg_c = 12345;
	lcg_m = 2147483648;
	table->lcg_seed = (lcg_a * table->lcg_seed + lcg_c) % lcg_m;
	return (table->lcg_seed);
}

long	get_time(char type)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("gettimeofday failed\n");
		// free
		exit (EXIT_FAILURE);
	}
	gettimeofday(&tv, NULL);
	if (type == 'a')
		return (tv.tv_sec + tv.tv_usec / 1000000);
	else
		return (tv.tv_sec * 1000000 + tv.tv_usec);
}
