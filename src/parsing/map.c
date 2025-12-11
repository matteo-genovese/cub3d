/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/12/11 11:02:12 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

void	fill_line_char(char *dest, char *src, int width, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(src);
	if (len > 0 && src[len - 1] == '\n')
		len--;
	while (i < len)
	{
		if (src[i] == '\t')
			dest[i] = c;
		else
			dest[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dest[i] = c;
		i++;
	}
	dest[i] = '\0';
}

void	clear_map(t_map *map)
{
	if (!map)
		return ;
	if (map->map)
	{
		free_map_array(map->map, map->height);
		map->map = NULL;
	}
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
}

static char	**convert_list_to_array(t_list *map_lines, int height, int width)
{
	char	**map;
	int		i;
	t_list	*current;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	current = map_lines;
	while (i < height && current)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!map[i])
			return (free_map_array(map, i), NULL);
		fill_line_char(map[i], (char *)current->content, width, ' ');
		current = current->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

static void	free_map_lines(t_list *map_lines)
{
	t_list	*current;
	t_list	*next;

	current = map_lines;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

int	parse_map(char *file_path, t_map *map)
{
	int		fd;
	t_list	*map_lines;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to open file\n"));
	skip_to_map(fd);
	map_lines = read_map_lines(fd);
	close(fd);
	get_next_line(-1);
	if (!map_lines || map_lines == NULL)
		return (1);
	init_map_struct(map, map_lines);
	map->map = convert_list_to_array(map_lines, map->height, map->width);
	free_map_lines(map_lines);
	if (!map->map)
		return (ft_error("Memory allocation failed\n"));
	if (validate_map(map))
	{
		clear_map(map);
		return (1);
	}
	space_to_one(map->map);
	return (0);
}
