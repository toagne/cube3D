/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:11:51 by omartela          #+#    #+#             */
/*   Updated: 2024/12/13 08:38:02 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *s1, t_table *table)
{
	if (!table->printf_flag)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(s1, 1);
		ft_putchar_fd('\n', 1);
	}
	table->printf_flag = 1;
}
