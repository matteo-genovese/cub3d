#include "cub3d.h"

int	render_loop(void *param)
{
	t_vars	*vars;
	static struct timeval ptv = {0, 0};
	struct timeval ctv;
	static int frame_count = 0;
	static double fps_timer = 0;

	vars = (t_vars *)param;
	gettimeofday(&ctv, NULL);

	double delta = (ctv.tv_sec - ptv.tv_sec) + (ctv.tv_usec - ptv.tv_usec) / 1000000.0;
	
	if (delta >= 1.0/FPS)
	{
		vars->move_speed = delta * 3.0;
		vars->rot_speed = delta * 1.0;
		move(vars);
		fps_timer += delta;
		frame_count++;
		if (fps_timer >= 1.0)
		{
			printf("FPS: %d\n", frame_count);
			frame_count = 0;
			fps_timer = 0;
		}
		ptv = ctv;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx_win	mlx;
	t_vars		vars;
	t_input		input;
	t_map		map;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>.cub\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (parse_input(argv[1], &input))
		exit(EXIT_FAILURE);
	if (parse_map(argv[1], &map))
		exit(EXIT_FAILURE);

	mlx = (t_mlx_win){0};
	mlx.mlx = NULL;
	mlx.win = NULL;
	init(&mlx);

	ft_memset(&vars, 0, sizeof(t_vars));
	vars.mlx = &mlx;
	
	vars.pos_x = map.player_x + 0.5;
	vars.pos_y = map.player_y + 0.5;
	
	if (map.player_dir == 'N')
	{
		vars.dir_x = -1;
		vars.dir_y = 0;
		vars.plane[0] = 0;
		vars.plane[1] = 0.66;
	}
	else if (map.player_dir == 'S')
	{
		vars.dir_x = 1;
		vars.dir_y = 0;
		vars.plane[0] = 0;
		vars.plane[1] = -0.66;
	}
	else if (map.player_dir == 'W')
	{
		vars.dir_x = 0;
		vars.dir_y = 1;
		vars.plane[0] = 0.66;
		vars.plane[1] = 0;
	}
	else if (map.player_dir == 'E')
	{
		vars.dir_x = 0;
		vars.dir_y = -1;
		vars.plane[0] = -0.66;
		vars.plane[1] = 0;
	}
	
	vars.move_speed = 0.1;
	vars.keys.right = 0;
	vars.keys.left = 0;
	
	// Usa i colori dalla struttura input parsata
	vars.ceiling_color = (input.ceiling.r << 16) | (input.ceiling.g << 8) | input.ceiling.b;
	vars.floor_color = (input.floor.r << 16) | (input.floor.g << 8) | input.floor.b;
	
	vars.map = map.map;
	// free_map_array(map.map, map.height);

	vars.textures[0].img = mlx_xpm_file_to_image(mlx.mlx, input.path_no, &vars.textures[0].width, &vars.textures[0].height);
	vars.textures[1].img = mlx_xpm_file_to_image(mlx.mlx, input.path_so, &vars.textures[1].width, &vars.textures[1].height);
	vars.textures[2].img = mlx_xpm_file_to_image(mlx.mlx, input.path_ea, &vars.textures[2].width, &vars.textures[2].height);
	vars.textures[3].img = mlx_xpm_file_to_image(mlx.mlx, input.path_we, &vars.textures[3].width, &vars.textures[3].height);
	if (!vars.textures[0].img || !vars.textures[1].img || 
		!vars.textures[2].img || !vars.textures[3].img)
	{
		printf("Error: Failed to load textures\n");
		exit(EXIT_FAILURE);
	}
	vars.textures[0].addr = mlx_get_data_addr(vars.textures[0].img, &vars.textures[0].bits_per_pixel,
					   &vars.textures[0].line_length, &vars.textures[0].endian);
	vars.textures[1].addr = mlx_get_data_addr(vars.textures[1].img, &vars.textures[1].bits_per_pixel,
					   &vars.textures[1].line_length, &vars.textures[1].endian);
	vars.textures[2].addr = mlx_get_data_addr(vars.textures[2].img, &vars.textures[2].bits_per_pixel,
					   &vars.textures[2].line_length, &vars.textures[2].endian);
	vars.textures[3].addr = mlx_get_data_addr(vars.textures[3].img, &vars.textures[3].bits_per_pixel,
					   &vars.textures[3].line_length, &vars.textures[3].endian);

	hooks(&vars);
	render(&vars);
	mlx_loop_hook(mlx.mlx, render_loop, &vars);
	mlx_loop(mlx.mlx);
	free_map_array(vars.map, map.height);
	return 0;
}
