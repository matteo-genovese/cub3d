#include "cub3d.h"

static void rotate_view(t_vars *vars, double angle)
{
	double oldDirX = vars->dir_x;
	double oldDirY = vars->dir_y;
	double oldPlaneX = vars->plane[0];
	double oldPlaneY = vars->plane[1];
	double c = cos(angle);
	double s = sin(angle);

	vars->dir_x = oldDirX * c - oldDirY * s;
	vars->dir_y = oldDirX * s + oldDirY * c;
	vars->plane[0] = oldPlaneX * c - oldPlaneY * s;
	vars->plane[1] = oldPlaneX * s + oldPlaneY * c;
}

int	destroy(t_vars *vars)
{
	if (vars->mlx)
	{
		if (vars->mlx->mlx)
		{
			if (vars->mlx->img)
				mlx_destroy_image(vars->mlx->mlx, vars->mlx->img);
			if (vars->mlx->win)
				mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
			mlx_destroy_display(vars->mlx->mlx);
			free(vars->mlx->mlx);
		}
		vars->mlx = NULL;
		exit(0);
	}
	return (0);
}

/* Key codes for movement
A: 97
S: 115
D: 100
W: 119
Left Arrow: 65361
Right Arrow: 65363
*/

int	key_press_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		destroy(vars);
	if (keycode == 119)
	{
		vars->pos_x += vars->dir_x * vars->move_speed;
		vars->pos_y += vars->dir_y * vars->move_speed;
	}
	if (keycode == 115)
	{
		vars->pos_x -= vars->dir_x * vars->move_speed;
		vars->pos_y -= vars->dir_y * vars->move_speed;
	}
	if (keycode == 97)
	{
		vars->pos_x -= vars->dir_y * vars->move_speed;
		vars->pos_y += vars->dir_x * vars->move_speed;
	}
	if (keycode == 100)
	{
		vars->pos_x += vars->dir_y * vars->move_speed;
		vars->pos_y -= vars->dir_x * vars->move_speed;
	}
	if (keycode == 65361)
		rotate_view(vars, vars->rot_speed);
	if (keycode == 65363)
		rotate_view(vars, -vars->rot_speed);
	render(vars);
	return (0);
}

void	hooks(t_vars *vars)
{
	printf("vars.pos_x: %f, vars->pos_y: %f\n", vars->pos_x, vars->pos_y);
	mlx_hook(vars->mlx->win, 17, 0, destroy, vars);
	mlx_key_hook(vars->mlx->win, key_press_handler, vars);
}

void	init(t_mlx_win *mlx_win)
{
	mlx_win->mlx = mlx_init();
	if (!(mlx_win->mlx))
	{
		perror("Failed to initialize mlx");
		exit(EXIT_FAILURE);
	}
	mlx_win->win = mlx_new_window(mlx_win->mlx, S_WIDTH, S_HEIGHT, "Cub3d");
	if (!(mlx_win->win))
	{
		perror("Failed to initialize windows");
		exit(EXIT_FAILURE);
	}

	/* create image buffer once */
	mlx_win->img = mlx_new_image(mlx_win->mlx, S_WIDTH, S_HEIGHT);
	if (!(mlx_win->img))
	{
		perror("Failed to create image");
		exit(EXIT_FAILURE);
	}
	mlx_win->addr = mlx_get_data_addr(mlx_win->img, &mlx_win->bits_per_pixel,
		&mlx_win->line_length, &mlx_win->endian);
}

