/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:39:55 by fde-sist          #+#    #+#             */
/*   Updated: 2025/11/27 17:18:29 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_loop(void *param)
{
	t_vars					*vars;
	static struct timeval	ptv;
	struct timeval			ctv;
	static double			fps_timer;
	double					delta;

	vars = (t_vars *)param;
	ctv.tv_sec = 0;
	ctv.tv_usec = 0;
	delta = (ctv.tv_sec - ptv.tv_sec) + (ctv.tv_usec - ptv.tv_usec) / 1000000.0;
	gettimeofday(&ctv, NULL);
	if (delta >= 1.0 / FPS)
	{
		vars->move_speed = delta * 3.0;
		vars->rot_speed = delta * 1.0;
		move(vars);
		fps_timer += delta;
		if (fps_timer >= 1.0)
			fps_timer = 0;
		ptv = ctv;
	}
	return (0);
}

void	load_texture(t_vars *vars, t_input *input, t_mlx_win *mlx, t_map *map)
{
	int	i;

	i = -1;
	vars->textures[0].img = mlx_xpm_file_to_image(mlx->mlx, input->path_so,
			&vars->textures[0].width, &vars->textures[0].height);
	vars->textures[1].img = mlx_xpm_file_to_image(mlx->mlx, input->path_no,
			&vars->textures[1].width, &vars->textures[1].height);
	vars->textures[2].img = mlx_xpm_file_to_image(mlx->mlx, input->path_ea,
			&vars->textures[2].width, &vars->textures[2].height);
	vars->textures[3].img = mlx_xpm_file_to_image(mlx->mlx, input->path_we,
			&vars->textures[3].width, &vars->textures[3].height);
	if (!vars->textures[0].img || !vars->textures[1].img
		|| !vars->textures[2].img || !vars->textures[3].img)
	{
		perror("Error: Failed to load textures\n");
		free_input(input);
		clear_map(map);
		exit(EXIT_FAILURE);
	}
	while (++i < 4)
		vars->textures[i].addr = mlx_get_data_addr(vars->textures[i].img,
				&vars->textures[i].bits_per_pixel,
				&vars->textures[i].line_length, &vars->textures[i].endian);
}

void	map_setup(t_vars *vars, t_input *input, t_map *map)
{
	if (map->player_dir == 'N')
	{
		vars->dir_x = -1;
		vars->plane[1] = +0.66;
	}
	else if (map->player_dir == 'S')
		vars->dir_x = 1;
	else if (map->player_dir == 'W')
	{
		vars->dir_y = -1;
		vars->plane[0] = -0.66;
		vars->plane[1] = 0.0;
	}
	else if (map->player_dir == 'E')
	{
		vars->dir_y = 1;
		vars->plane[0] = +0.66;
		vars->plane[1] = 0.0;
	}
	vars->ceiling_color = (input->ceiling.r << 16)
		| (input->ceiling.g << 8) | input->ceiling.b;
	vars->floor_color = (input->floor.r << 16)
		| (input->floor.g << 8) | input->floor.b;
	vars->map_height = map->height;
	load_texture(vars, input, vars->mlx, map);
}

void	starting_check(int argc, char **argv, t_input *input, t_map *map)
{
	if (argc != 2)
	{
		printf("Usage: %s <map_file>.cub\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (parse_input(argv[1], input))
	{
		free_input(input);
		exit(EXIT_FAILURE);
	}
	if (parse_map(argv[1], map))
	{
		free_input(input);
		clear_map(map);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_mlx_win	mlx;
	t_vars		vars;
	t_input		input;
	t_map		map;

	ft_memset(&map, 0, sizeof(t_map));
	starting_check(argc, argv, &input, &map);
	init(&mlx);
	ft_memset(&vars, 0, sizeof(t_vars));
	vars.mlx = &mlx;
	vars.map = map.map;
	vars.pos_x = map.player_y + 0.5;
	vars.pos_y = map.player_x + 0.5;
	vars.move_speed = 0.1;
	vars.rot_speed = 0.15;
	vars.plane[1] = -0.66;
	vars.plane[0] = 0.0;
	map_setup(&vars, &input, &map);
	free_input(&input);
	hooks(&vars);
	render(&vars);
	mlx_loop_hook(mlx.mlx, render_loop, &vars);
	mlx_loop(mlx.mlx);
	return (0);
}
