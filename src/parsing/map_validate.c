/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/12/11 11:13:36 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = c;
		i++;
	}
}

void	space_to_one(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		space_to_char(str[i], '1');
		i++;
	}
}

int	validate_map(t_map *map)
{
	t_map	tmp;
	size_t	i;

	if (find_player(map))
		return (1);
	i = 0;
	tmp.height = map->height + 2;
	tmp.width = map->width + 2;
	tmp.map = (char **) malloc(sizeof(char *) * (tmp.height + 1));
	tmp.map[tmp.height] = 0;
	if (!tmp.map)
		return (ft_error("Memory allocation failed\n"));
	while (i < (size_t) tmp.height)
	{
		tmp.map[i] = (char *)malloc(sizeof(char) * (tmp.width + 1));
		ft_memset(tmp.map[i], 'K', tmp.width);
		tmp.map[i][tmp.width] = '\0';
		if (!tmp.map[i])
			return (ft_error("Memory allocation failed\n"));
		if (i != 0 && i != (size_t) tmp.height - 1)
			ft_memcpy(tmp.map[i] + 1, map->map[i - 1], map->width);
		space_to_char(tmp.map[i], 'K');
		i++;
	}
	return (check_walls(&tmp));
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
