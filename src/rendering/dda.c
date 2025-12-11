/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:36:15 by fde-sist          #+#    #+#             */
/*   Updated: 2025/12/11 13:39:51 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Puts a pixel of a given color at (x, y) in the mlx window image
 */
void	my_mlx_pixel_put(t_mlx_win *mlx_win, int x, int y, int color)
{
	char	*dst;
	int		bpp_bytes;

	if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT)
		return ;
	bpp_bytes = mlx_win->bits_per_pixel / 8;
	dst = mlx_win->addr + (y * mlx_win->line_length + x * bpp_bytes);
	*(unsigned int *)dst = (unsigned int)color;
}

/*
 * Initializes the image for rendering with floor and ceiling colors
 */
void	image_startup(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (vars->mlx && vars->mlx->addr)
	{
		while (x < S_WIDTH)
		{
			y = 0;
			while (y < S_HEIGHT / 2)
			{
				my_mlx_pixel_put(vars->mlx, x, y, vars->ceiling_color);
				y++;
			}
			while (y < S_HEIGHT)
			{
				my_mlx_pixel_put(vars->mlx, x, y, vars->floor_color);
				y++;
			}
			x++;
		}
	}
}

/*
 * Sets up the initial vectors for the raycasting
 */
void	vectors_setup(t_vars *vars, t_vectors *v, int i)
{
	v->camera[0] = 2 * i / (double)S_WIDTH - 1;
	v->ray[0] = vars->dir_x + vars->plane[0] * v->camera[0];
	v->ray[1] = vars->dir_y + vars->plane[1] * v->camera[0];
	v->map[0] = (int)vars->pos_x;
	v->map[1] = (int)vars->pos_y;
	if (v->ray[0] == 0.0)
		v->deltadist[0] = 1e30;
	else
		v->deltadist[0] = fabs(1.0 / v->ray[0]);
	if (v->ray[1] == 0.0)
		v->deltadist[1] = 1e30;
	else
		v->deltadist[1] = fabs(1.0 / v->ray[1]);
	v->step[0] = -1 * (v->ray[0] < 0) + 1 * (v->ray[0] >= 0);
	v->sidedist[0] = (-vars->pos_x + v->map[0] + 1)
		* v->deltadist[0];
	if (v->ray[0] < 0)
		v->sidedist[0] = (vars->pos_x - v->map[0]) * v->deltadist[0];
	v->step[1] = -1 * (v->ray[1] < 0) + 1 * (v->ray[1] >= 0);
	v->sidedist[1] = (-vars->pos_y + v->map[1] + 1)
		* v->deltadist[1];
	if (v->ray[1] < 0)
		v->sidedist[1] = (vars->pos_y - v->map[1]) * v->deltadist[1];
}

/*
 * Performs the DDA algorithm to find the wall hit
 */
void	perform_dda(t_vars *vars, t_vectors v,
		int *side, double *perp_wall_dist)
{
	int		hit;
	int		dir;
	size_t	iter;

	hit = 0;
	iter = 0;
	while (hit == 0 && iter < MAX_ITER)
	{
		dir = !(v.sidedist[0] < v.sidedist[1]);
		v.sidedist[dir] += v.deltadist[dir];
		v.map[dir] += v.step[dir];
		*side = 0 + 2 * dir;
		if (v.step[dir] > 0)
			*side = 1 + 2 * dir;
		if (vars->map[v.map[0]][v.map[1]] == '1')
			hit = 1;
		iter++;
	}
	if (iter == MAX_ITER)
		return ;
	*perp_wall_dist = (v.sidedist[1] - v.deltadist[1]);
	if (*side == 0 || *side == 1)
		*perp_wall_dist = (v.sidedist[0] - v.deltadist[0]);
	if (*perp_wall_dist == 0.0)
		*perp_wall_dist = 1e-6;
}

/*
* Renders a frame based on vars content
* side encoding: 0 - North, 1 - South, 2 - East, 3 - West
*/
void	render(t_vars *vars)
{
	int			i;
	int			side;
	t_vectors	v;
	double		perp_wall_dist;
	int			line_height;

	if (!vars)
		return ;
	i = 0;
	v.sidedist[0] = 0.0;
	v.sidedist[1] = 0.0;
	image_startup(vars);
	i = 0;
	while (i < S_WIDTH)
	{
		vectors_setup(vars, &v, i);
		perform_dda(vars, v, &side, &perp_wall_dist);
		line_height = (int)(S_HEIGHT / perp_wall_dist);
		v.draw[0] = -line_height / 2 + S_HEIGHT / 2;
		v.draw[1] = line_height / 2 + S_HEIGHT / 2;
		draw_vertical_texture(vars, (int []){i, side}, v, perp_wall_dist);
		i++;
	}
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->mlx->img, 0, 0);
}
