/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:40:15 by fde-sist          #+#    #+#             */
/*   Updated: 2025/11/27 15:51:30 by fde-sist         ###   ########.fr       */
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

static void	destroy_textures(t_vars *vars)
{
	int	i;

	if (!vars || !vars->mlx || !vars->mlx->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (vars->textures[i].img)
		{
			mlx_destroy_image(vars->mlx->mlx, vars->textures[i].img);
			vars->textures[i].img = NULL;
			vars->textures[i].addr = NULL;
		}
		i++;
	}
}

int	destroy(t_vars *vars)
{
	if (vars->map)
	{
		free_map_array(vars->map, vars->map_height);
		vars->map = NULL;
	}
	destroy_textures(vars);
	if (vars->mlx)
	{
		if (vars->mlx->mlx)
		{
			if (vars->mlx->img)
			{
				mlx_destroy_image(vars->mlx->mlx, vars->mlx->img);
				vars->mlx->img = NULL;
				vars->mlx->addr = NULL;
			}
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
