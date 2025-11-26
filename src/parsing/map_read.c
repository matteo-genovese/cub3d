/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/26 22:55:54 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_to_map(int fd)
{
	char	*line;
	char	*trimmed;
	int		settings_count;

	settings_count = 0;
	while (settings_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			get_next_line(-1);
			return ;
		}
		trimmed = line;
		while (*trimmed == ' ' || *trimmed == '\t')
			trimmed++;
		if (ft_strncmp(trimmed, "NO ", 3) == 0
			|| ft_strncmp(trimmed, "SO ", 3) == 0
			|| ft_strncmp(trimmed, "WE ", 3) == 0
			|| ft_strncmp(trimmed, "EA ", 3) == 0
			|| ft_strncmp(trimmed, "F ", 2) == 0
			|| ft_strncmp(trimmed, "C ", 2) == 0)
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

static int	has_map_content_after(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

static t_list	*handle_map_end(int fd, t_list *map_lines, char *line)
{
	free(line);
	if (has_map_content_after(fd))
	{
		ft_lstclear(&map_lines, free);
		ft_error("Map must be continuous (no empty lines)\n");
		return (NULL);
	}
	return (map_lines);
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
			return (handle_map_end(fd, map_lines, line));
		free(line);
	}
	if (!map_lines)
		ft_error("No map found in file\n");
	return (map_lines);
}
