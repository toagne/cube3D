/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:34:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/12/07 19:09:29 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int h, int w, char labeled_map[h][w], t_door_helper door)
{
	if (door.x < 0 || door.y < 0 || door.x >= w || door.y >= h || labeled_map[door.y][door.x] != '0')
		return ;
	labeled_map[door.y][door.x] = door.label + '0';
	door.x += 1;
	flood_fill(h, w, labeled_map, door);
	door.x -= 2;
	flood_fill(h, w, labeled_map, door);
	door.x += 1;
	door.y += 1;
	flood_fill(h, w, labeled_map, door);
	door.y -= 2;
	flood_fill(h, w, labeled_map, door);
}

void	place_doors(t_table *table, int door_index, t_door_helper *door)
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

void	label_map(int h, int w, char labeled_map[h][w], t_door_helper *helper)
{
	helper->room_1 = '0';
	helper->room_2 = '0';
	if (labeled_map[helper->y - 1][helper->x] > 1 + '0')
		helper->room_1 = labeled_map[helper->y - 1][helper->x];
	if (labeled_map[helper->y + 1][helper->x] > 1 + '0')
	{
		if (helper->room_2 == '0')
			helper->room_2 = labeled_map[helper->y + 1][helper->x];
	}
	if (labeled_map[helper->y][helper->x - 1] > 1 + '0')
	{
		if (helper->room_1 == '0')
			helper->room_1 = labeled_map[helper->y][helper->x - 1];
	}
	if (labeled_map[helper->y][helper->x + 1] > 1 + '0')
	{
		if (helper->room_2 == '0')
			helper->room_2 = labeled_map[helper->y][helper->x + 1];
	}
}

void	find_walls_separating_rooms(t_table *table, int h, int w, char labeled_map[h][w])
{
	t_door_helper	temp_door[h * w];
	t_door_helper	helper;

	helper.door_index = 0;
	helper.y = 0;
	while (++helper.y < h - 1)
	{
		helper.x = 0;
		while (++helper.x < w - 1)
		{
			if (labeled_map[helper.y][helper.x] == '1')
			{
				label_map(h, w, labeled_map, &helper);
				if (helper.room_1 != '0' && helper.room_2 != '0' && helper.room_1 != helper.room_2)
				{
					temp_door[helper.door_index].x = helper.x;
					temp_door[helper.door_index].y = helper.y;
					temp_door[helper.door_index].room_1 = helper.room_1;
					temp_door[helper.door_index].room_2 = helper.room_2;
					helper.door_index++;
				}
			}
		}
	}
	place_doors(table, helper.door_index, temp_door);
}

void	add_doors(t_table *table)
{
	char			labeled_map[table->rows][table->columns];
	t_door_helper	door;

	door.y = -1;
	while (++door.y < (int)table->rows)
	{
		door.x = -1;
		while (++door.x < (int)table->columns)
			labeled_map[door.y][door.x] = table->map[door.y][door.x];
	}
	door.label = 2;
	door.y = -1;
	while (++door.y < (int)table->rows)
	{
		door.x = -1;
		while (++door.x < (int)table->columns)
		{
			if (labeled_map[door.y][door.x] == '0')
			{
				flood_fill(table->rows, table->columns, labeled_map, door);
				door.label++;
			}
		}
	}
	find_walls_separating_rooms(table, table->rows, table->columns, labeled_map);
}
