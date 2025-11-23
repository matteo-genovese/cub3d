/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:50:58 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int	check_texture_format(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (-1);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (-1);
	return (0);
}

static char	*trim_path(char *str)
{
	char	*end;
	int		len;

	str = skip_whitespace(str);
	end = str;
	while (*end && *end != '\n' && *end != ' ' && *end != '\t')
		end++;
	len = end - str;
	return (ft_substr(str, 0, len));
}

char	*parse_texture_path(char *line)
{
	char	*path;
	int		fd;

	path = trim_path(line);
	if (!path || !*path)
	{
		if (path)
			free(path);
		ft_error("Invalid texture path\n");
		return (NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1 || check_texture_format(path) == -1)
	{
		free(path);
		if (fd == -1)
			ft_error("Texture file not found\n");
		else
			ft_error("Invalid texture format (must be .xpm)\n");
		return (NULL);
	}
	close(fd);
	return (path);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
