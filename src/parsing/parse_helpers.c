/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:49:38 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == '\t' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	is_map_line(char *line)
{
	int	i;
	int	has_content;

	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ' && line[i] != '\t')
			has_content = 1;
		i++;
	}
	return (has_content);
}
