/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:52:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/26 22:55:54 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_max_width(t_list *map_lines)
{
	int		max_width;
	int		len;
	t_list	*current;

	max_width = 0;
	current = map_lines;
	while (current)
	{
		len = ft_strlen((char *)current->content);
		if (len > 0 && ((char *)current->content)[len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		current = current->next;
	}
	return (max_width);
}

void	init_map_struct(t_map *map, t_list *map_lines)
{
	map->height = ft_lstsize(map_lines);
	map->width = get_max_width(map_lines);
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
}
