#include "cub3d.h"

int	render_loop(void *param)
{
	t_vars	*vars;
	static double fps;
	struct timeval	ctv;
	static struct timeval	ptv;
	gettimeofday(&ctv, NULL);
	vars = (t_vars *)param;

	double delta = (ctv.tv_sec - ptv.tv_sec) + (ctv.tv_usec - ptv.tv_usec) / 1000000.0;
	if (delta >= 1.0)
    {
        fps = (double)1.0 / delta;
        printf("FPS: %.2lf, delta: %.2lf\n", fps, delta);
        ptv = ctv;
    }
	// vars->move_speed = delta * 5.0; // adjust multiplier for desired speed
	// vars->rot_speed = delta * 1.0;  // adjust multiplier for desired

	// render(vars);
	return (0);
}

int	main(void)
{
	t_mlx_win	mlx;
	t_vars		vars;

	mlx.mlx = NULL;
	mlx.win = NULL;
	init(&mlx);


	vars.mlx = &mlx;
	vars.pos_x = 22;
	vars.pos_y = 11;
	vars.dir_x = -1;
	vars.dir_y = 0;
	vars.plane[0] = 0;
	vars.plane[1] = 0.66;
	vars.move_speed = 0.5;
	vars.rot_speed = acos(-1.0) / 12.0;
	hooks(&vars);
	render(&vars);
	// mlx_loop_hook(mlx.mlx, render_loop, &vars);
	mlx_loop(mlx.mlx);
	return 0;
}
