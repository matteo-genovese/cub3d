#include "cub3d.h"

int	destroy(t_mlx_win *vars)
{
	if (vars)
	{
		if (vars->mlx)
		{
			if (vars->win)
				mlx_destroy_window(vars->mlx, vars->win);
			mlx_destroy_display(vars->mlx);
			free(vars->mlx);
		}
		vars = NULL;
		exit(0);
	}
	return (0);
}

int	key_press_handler(int keycode, t_mlx_win *vars)
{
	if (keycode == 65307)
		destroy(vars);
	return (0);
}

void	hooks(t_mlx_win *vars)
{
	mlx_hook(vars->win, 17, 0, destroy, vars);
	mlx_key_hook(vars->win, key_press_handler, vars);
}

void	init(t_mlx_win *vars)
{
	vars->mlx = mlx_init();
	if (!(vars->mlx))
	{
		perror("Failed to initialize mlx");
		exit(EXIT_FAILURE);
	}
	vars->win = mlx_new_window(vars->mlx, S_WIDTH, S_HEIGHT, "Cub3d");
	if (!(vars->win))
	{
		perror("Failed to initialize windows");
		exit(EXIT_FAILURE);
	}
	hooks(vars);
}

