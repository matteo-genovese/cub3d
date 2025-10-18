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
		render(vars);
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


int	main(void)
{
	t_mlx_win	mlx;
	t_vars		vars;
	void		*img;

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
	load_map(&vars, worldMap);

	// Load texture after mlx is properly initialized
	img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[0].width, &vars.textures[0].height);
	if (!img)
	{
		printf("Error: Failed to load texture 'textures/bricks.xpm'\n");
		exit(EXIT_FAILURE);
	}
	vars.textures[0].img = img;
	vars.textures[1].img = mlx_xpm_file_to_image(mlx.mlx, "textures/bricks.xpm", &vars.textures[1].width, &vars.textures[1].height);
	if (!vars.textures[1].img)
	{
		printf("Error: Failed to load texture 'textures/bricks.xpm'\n");
		exit(EXIT_FAILURE);
	}
	vars.textures[1].addr = mlx_get_data_addr(vars.textures[1].img, &vars.textures[1].bits_per_pixel,
					   &vars.textures[1].line_length, &vars.textures[1].endian);
	vars.textures[0].addr = mlx_get_data_addr(img, &vars.textures[0].bits_per_pixel,
					   &vars.textures[0].line_length, &vars.textures[0].endian);

	hooks(&vars);
	render(&vars);
	mlx_loop_hook(mlx.mlx, render_loop, &vars);
	mlx_loop(mlx.mlx);
	return 0;
}
