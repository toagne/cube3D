/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:34:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/05 12:00:35 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int h, int w, char labeled_map[h][w], int x, int y, int label)
{
	if (x < 0 || y < 0 || x >= w || y >= h || labeled_map[y][x] != '0')
		return ;
	labeled_map[y][x] = label + '0';
	flood_fill(h, w, labeled_map, x + 1, y, label);
	flood_fill(h, w, labeled_map, x - 1, y, label);
	flood_fill(h, w, labeled_map, x, y + 1, label);
	flood_fill(h, w, labeled_map, x, y - 1, label);
}

void	place_doors(t_table *table, int door_index, t_door *door)
{
	int	i;
	int	room_1;
	int	room_2;
	int	door_exists;
	int	j;

	i = -1;
	while (++i < door_index)
	{
		room_1 = door[i].room_1;
		room_2 = door[i].room_2;
		door_exists = 0;
		j = -1;
		while (++j < i)
		{
			if ((door[j].room_1 == room_1 && door[j].room_2 == room_2) || (door[j].room_1 == room_2 && door[j].room_2 == room_1))
			{
				door_exists = 1;
				break ;
			}
		}
		if (!door_exists)
			table->map[door[i].y][door[i].x] = '2';
	}
}

/* void	label_map(int x, int y, char labeled_map[y][x], int door_index)
{
	char	room_1;
	char	room_2;

	if (labeled_map[y][x] == '1')
	{
		room_1 = '0';
		room_2 = '0';
		if (labeled_map[y - 1][x] > 1 + '0')
			room_1 = labeled_map[y - 1][x];
		if (labeled_map[y + 1][x] > 1 + '0')
		{
			if (room_2 == '0')
				room_2 = labeled_map[y + 1][x];
		}
		if (labeled_map[y][x - 1] > 1 + '0')
		{
			if (room_1 == '0')
				room_1 = labeled_map[y][x - 1];
		}
		if (labeled_map[y][x + 1] > 1 + '0')
		{
			if (room_2 == '0')
				room_2 = labeled_map[y][x + 1];
		}
		if (room_1 != '0' && room_2 != '0' && room_1 != room_2)
		{
			temp_door[door_index].x = x;
			temp_door[door_index].y = y;
			temp_door[door_index].room_1 = room_1;
			temp_door[door_index].room_2 = room_2;
			door_index++;
		}
	}
} */

void	find_walls_separating_rooms(t_table *table, int h, int w, char labeled_map[h][w])
{
	int		y;
	int		x;
	char	room_1;
	char	room_2;
	t_door	temp_door[h * w];
	int		door_index;

	door_index = 0;
	y = 0;
	while (++y < h - 1)
	{
		x = 0;
		while (++x < w - 1)
		{
			if (labeled_map[y][x] == '1')
			{
				room_1 = '0';
				room_2 = '0';
				if (labeled_map[y - 1][x] > 1 + '0')
					room_1 = labeled_map[y - 1][x];
				if (labeled_map[y + 1][x] > 1 + '0')
				{
					if (room_2 == '0')
						room_2 = labeled_map[y + 1][x];
				}
				if (labeled_map[y][x - 1] > 1 + '0')
				{
					if (room_1 == '0')
						room_1 = labeled_map[y][x - 1];
				}
				if (labeled_map[y][x + 1] > 1 + '0')
				{
					if (room_2 == '0')
						room_2 = labeled_map[y][x + 1];
				}
				if (room_1 != '0' && room_2 != '0' && room_1 != room_2)
				{
					temp_door[door_index].x = x;
					temp_door[door_index].y = y;
					temp_door[door_index].room_1 = room_1;
					temp_door[door_index].room_2 = room_2;
					door_index++;
				}
			}
		}
	}
	place_doors(table, door_index, temp_door);
}

void	add_doors(t_table *table)
{
	char	labeled_map[table->rows][table->columns];
	int		y;
	int		x;
	int		label;
	int		h;
	int		w;

	h = table->rows;
	w = table->columns;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			labeled_map[y][x] = table->map[y][x];
	}
	label = 2;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			if (labeled_map[y][x] == '0')
			{
				flood_fill(h, w, labeled_map, x, y, label);
				label++;
			}
		}
	}
	find_walls_separating_rooms(table, h, w, labeled_map);
}
