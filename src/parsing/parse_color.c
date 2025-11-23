/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:49:45 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	count_elements(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (str[i] == '\0' || str[i] == '\n');
}

static int	parse_rgb_values(char **split, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!is_valid_number(split[0]) || !is_valid_number(split[1])
		|| !is_valid_number(split[2]))
		return (ft_error("Invalid RGB format\n"));
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		return (ft_error("RGB values must be in range [0, 255]\n"));
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

int	parse_color(char *line, t_color *color)
{
	char	**split;
	int		result;

	split = ft_split(line, ',');
	if (!split)
		return (ft_error("Memory allocation failed\n"));
	if (count_elements(split) != 3)
	{
		free_split(split);
		return (ft_error("Color must have exactly 3 RGB values\n"));
	}
	result = parse_rgb_values(split, color);
	free_split(split);
	return (result);
}
