/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/10/17 17:50:51 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c);

int	find_player(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player_char(map->map[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->map[y][x];
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (ft_error("Map must have exactly one player\n"));
	return (0);
}

int	validate_map(t_map *map)
{
	if (find_player(map))
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}
