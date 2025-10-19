/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/10/19 18:32:14 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_neighbor(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	return (map->map[y][x] == '1');
}

int	check_neighbor(t_map *map, int y, int x)
{
	if (!is_valid_neighbor(map, y, x) && map->map[y][x] != '0'
		&& !is_player_char(map->map[y][x]))
		return (ft_error("Map not surrounded by walls\n"));
	return (0);
}

int	check_position(t_map *map, int y, int x)
{
	if (map->map[y][x] != '0' && !is_player_char(map->map[y][x]))
		return (0);
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		return (ft_error("Map not surrounded by walls\n"));
	if (check_neighbor(map, y - 1, x))
		return (1);
	if (check_neighbor(map, y + 1, x))
		return (1);
	if (check_neighbor(map, y, x - 1))
		return (1);
	if (check_neighbor(map, y, x + 1))
		return (1);
	return (0);
}

int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (check_position(map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

