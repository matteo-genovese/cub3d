#include "cub3d.h"

int		worldMap[mapWidth][mapHeight] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
	void		*img;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>.cub\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (parse_input(argv[1], &input))
		exit(EXIT_FAILURE);
	if (parse_map(argv[1], &map))
		exit(EXIT_FAILURE);

	mlx.mlx = NULL;
	mlx.win = NULL;
	init(&mlx);

	// Initialize vars structure first
	ft_memset(&vars, 0, sizeof(t_vars));
	vars.mlx = &mlx;
	vars.pos_x = 22;
	vars.pos_y = 11;
	vars.dir_x = -1;
	vars.dir_y = 0;
	vars.plane[0] = 0;
	vars.plane[1] = 0.66;
	vars.move_speed = 0.1;
	vars.keys.right = 0;
	vars.keys.left = 0;
	vars.ceiling_color = 0x87CEEB; // Light blue
	vars.floor_color = 0x228B22;   // Forest green
	load_map(&vars, worldMap);

	vars.textures[0].img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[0].width, &vars.textures[0].height);
	vars.textures[1].img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[1].width, &vars.textures[1].height);
	vars.textures[2].img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[2].width, &vars.textures[2].height);
	vars.textures[3].img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[3].width, &vars.textures[3].height);
	if (!vars.textures[1].img)
	{
		printf("Error: Failed to load texture 'textures/bricks.xpm'\n");
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
	return 0;
}
