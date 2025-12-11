/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/12/11 11:03:47 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	free_map_array(char **map, int i)
{
	while (i > 0)
		free(map[--i]);
	free(map);
}

int	flood_fill_check(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width
		|| map->map[y][x] == 'V' || map->map[y][x] == '1')
		return (0);
	if (map->map[y][x] == '0')
		return (ft_error("Map is not enclosed by walls\n"));
	map->map[y][x] = 'V';
	if (flood_fill_check(map, y - 1, x))
		return (1);
	if (flood_fill_check(map, y + 1, x))
		return (1);
	if (flood_fill_check(map, y, x - 1))
		return (1);
	if (flood_fill_check(map, y, x + 1))
		return (1);
	return (0);
}

int	check_walls(t_map *map)
{
	int	ret;

	ret = flood_fill_check(map, 0, 0);
	free_map_array(map->map, map->height);
	return (ret);
}
