/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/12/10 19:19:26 by mgenoves         ###   ########.fr       */
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

void	space_to_char(char *str, char c)
{
	while (*str)
	{
		if (*str == ' ')
			*str = c;
		str++;
	}
}

int	validate_map(t_map *map)
{
	t_map	tmp;
	size_t	i;

	if (find_player(map))
		return (1);
	i = 1;
	tmp.height = map->height + 2;
	tmp.width = map->width + 2;
	tmp.map = (char **) malloc(sizeof(char *) * (tmp.height + 1));
	if (!tmp.map)
		return (ft_error("Memory allocation failed\n"));
	tmp.map[0] = (char *)malloc(sizeof(char) * (tmp.width + 1));
	tmp.map[tmp.height - 1] = (char *)malloc(sizeof(char) * (tmp.width + 1));
	ft_memset(tmp.map[0], 'K', tmp.width);
	ft_memset(tmp.map[tmp.height - 1], 'K', tmp.width);
	while (i < (size_t) tmp.height -1)
	{
		tmp.map[i] = (char *)malloc(sizeof(char) * (tmp.width + 1));
		ft_memset(tmp.map[i], 'K', tmp.width);
		if (!tmp.map[i])
			return (ft_error("Memory allocation failed\n"));
		ft_memcpy(tmp.map[i] + 1, map->map[i - 1], map->width);
		space_to_char(tmp.map[i], 'K');
		i++;
	}
	if (check_walls(&tmp))
	{
		free_map_array(tmp.map, tmp.height);
		free(tmp.map);
		return (1);
	}
	return (0);
}

void	free_input(t_input *input)
{
	if (!input)
		return ;
	free(input->path_no);
	free(input->path_so);
	free(input->path_we);
	free(input->path_ea);
	input->path_no = NULL;
	input->path_so = NULL;
	input->path_we = NULL;
	input->path_ea = NULL;
	input->has_no = 0;
	input->has_so = 0;
	input->has_we = 0;
	input->has_ea = 0;
	input->has_floor = 0;
	input->has_ceiling = 0;
}

void	free_map_array(char **map, int i)
{
	while (i > 0)
		free(map[--i]);
	free(map);
}
