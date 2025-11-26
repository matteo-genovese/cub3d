/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/26 22:14:56 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

static int	try_parse_setting(char *line, t_input *input)
{
	int	result;

	result = parse_no_so(line, input);
	if (result != -1)
		return (result);
	result = parse_we_ea(line, input);
	if (result != -1)
		return (result);
	result = parse_floor_ceiling(line, input);
	if (result != -1)
		return (result);
	return (-1);
}

static int	process_line(char *line, t_input *input)
{
	int	result;

	if (is_empty_line(line))
		return (0);
	result = try_parse_setting(line, input);
	if (result == -1)
	{
		if (all_settings_found(input) && is_map_line(line))
			return (2);
		return (ft_error("Invalid line or incomplete settings\n"));
	}
	return (result);
}

static int	process_result(int result)
{
	if (result != 0)
	{
		if (result == 2)
			return (0);
		return (1);
	}
	return (-1);
}

static int	read_settings(int fd, t_input *input)
{
	char	*line;
	int		result;
	char	*trimmed_line;

	while (1)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, " \t\n");
		free(line);
		if (!trimmed_line)
			break ;
		result = process_line(trimmed_line, input);
		free(trimmed_line);
		result = process_result(result);
		if (result != -1)
		{
			get_next_line(-1);
			return (result);
		}
	}
	get_next_line(-1);
	if (!all_settings_found(input))
		return (ft_error("Missing required settings\n"));
	return (0);
}

int	parse_input(char *file_path, t_input *input)
{
	int	fd;
	int	result;
	int	len;

	init_input(input);
	len = ft_strlen(file_path);
	if (file_path[len - 4] != '.' || file_path[len - 3] != 'c'
		|| file_path[len - 2] != 'u' || file_path[len - 1] != 'b')
		return (ft_error("File must have a .cub extension\n"));
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to open file\n"));
	result = read_settings(fd, input);
	close(fd);
	if (result != 0)
		get_next_line(-1);
	return (result);
}
