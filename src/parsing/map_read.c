/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/06 13:06:25 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_to_map(int fd)
{
	char	*line;
	int		settings_count;

	settings_count = 0;
	while (settings_count < 6)
	{
		printf("Skipping non-map lines...\n");
		line = get_next_line(fd);
		printf("Skipping line: %s", line);
		if (!line)
			return ;
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0)
			settings_count++;
		free(line);
	}
}

static void	add_line_to_list(t_list **map_lines, char *line)
{
	t_list	*new_node;
	char	*line_copy;

	line_copy = ft_strdup(line);
	if (!line_copy)
		return ;
	new_node = ft_lstnew(line_copy);
	if (!new_node)
	{
		free(line_copy);
		return ;
	}
	ft_lstadd_back(map_lines, new_node);
}

t_list	*read_map_lines(int fd)
{
	t_list	*map_lines;
	char	*line;
	int		started;

	map_lines = NULL;
	started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(line))
		{
			add_line_to_list(&map_lines, line);
			started = 1;
		}
		else if (started && !is_map_line(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (map_lines);
}

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

