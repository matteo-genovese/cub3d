/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:34:10 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_no_so(char *line, t_input *input)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (input->has_no)
			return (ft_error("Duplicate NO texture\n"));
		input->path_no = parse_texture_path(line + 3);
		if (!input->path_no)
			return (1);
		input->has_no = 1;
		return (0);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (input->has_so)
			return (ft_error("Duplicate SO texture\n"));
		input->path_so = parse_texture_path(line + 3);
		if (!input->path_so)
			return (1);
		input->has_so = 1;
		return (0);
	}
	return (-1);
}

int	parse_we_ea(char *line, t_input *input)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (input->has_we)
			return (ft_error("Duplicate WE texture\n"));
		input->path_we = parse_texture_path(line + 3);
		if (!input->path_we)
			return (1);
		input->has_we = 1;
		return (0);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (input->has_ea)
			return (ft_error("Duplicate EA texture\n"));
		input->path_ea = parse_texture_path(line + 3);
		if (!input->path_ea)
			return (1);
		input->has_ea = 1;
		return (0);
	}
	return (-1);
}

int	parse_floor_ceiling(char *line, t_input *input)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (input->has_floor)
			return (ft_error("Duplicate floor color\n"));
		if (parse_color(skip_whitespace(line + 2), &input->floor))
			return (1);
		input->has_floor = 1;
		return (0);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (input->has_ceiling)
			return (ft_error("Duplicate ceiling color\n"));
		if (parse_color(skip_whitespace(line + 2), &input->ceiling))
			return (1);
		input->has_ceiling = 1;
		return (0);
	}
	return (-1);
}

int	all_settings_found(t_input *input)
{
	return (input->has_no && input->has_so && input->has_we
		&& input->has_ea && input->has_floor && input->has_ceiling);
}

void	init_input(t_input *input)
{
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
