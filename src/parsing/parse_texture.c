/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/10/17 17:50:51 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

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
	if (fd == -1)
	{
		free(path);
		ft_error("Texture file not found\n");
		return (NULL);
	}
	close(fd);
	return (path);
}

