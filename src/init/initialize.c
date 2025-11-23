/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:40:15 by fde-sist          #+#    #+#             */
/*   Updated: 2025/11/23 17:28:51 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		destroy(vars);
	if (keycode == 119)
		vars->keys.w = 1;
	if (keycode == 115)
		vars->keys.s = 1;
	if (keycode == 97)
		vars->keys.a = 1;
	if (keycode == 100)
		vars->keys.d = 1;
	if (keycode == 65361)
		vars->keys.left = 1;
	if (keycode == 65363)
		vars->keys.right = 1;
	move(vars);
	return (0);
}

int	key_release_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		destroy(vars);
	if (keycode == 119)
		vars->keys.w = 0;
	if (keycode == 115)
		vars->keys.s = 0;
	if (keycode == 97)
		vars->keys.a = 0;
	if (keycode == 100)
		vars->keys.d = 0;
	if (keycode == 65361)
		vars->keys.left = 0;
	if (keycode == 65363)
		vars->keys.right = 0;
	return (0);
}

int	destroy(t_vars *vars)
{
    if (vars->map)
    {
        free_map_array(vars->map, vars->map_height);
        vars->map = NULL;
        vars->map_height = 0;
    }
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

void	hooks(t_vars *vars)
{
	mlx_hook(vars->mlx->win, 17, 0, destroy, vars);
	mlx_hook(vars->mlx->win, 2, (1L << 0), key_press_handler, vars);
	mlx_hook(vars->mlx->win, 3, (1L << 1), key_release_handler, vars);
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
	mlx_win->img = mlx_new_image(mlx_win->mlx, S_WIDTH, S_HEIGHT);
	if (!(mlx_win->img))
	{
		perror("Failed to create image");
		exit(EXIT_FAILURE);
	}
	mlx_win->addr = mlx_get_data_addr(mlx_win->img, &mlx_win->bits_per_pixel,
			&mlx_win->line_length, &mlx_win->endian);
}
