/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:39:21 by fde-sist          #+#    #+#             */
/*   Updated: 2025/11/23 17:52:06 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Performs the drawing loop for a vertical stripe
 */
void	draw_loop(t_vars *vars, int x, t_vectors v, int side)
{
	double	step;
	double	texture_pos;
	int		color;

	step = 1.0 * vars->textures[side].height / (v.draw[1] - v.draw[0]);
	texture_pos = (v.draw[0] - S_HEIGHT / 2
			+ (v.draw[1] - v.draw[0]) / 2) * step;
	if (v.draw[1] >= S_HEIGHT)
		v.draw[1] = S_HEIGHT - 1;
	if (v.draw[0] < 0)
	{
		texture_pos = step * (-v.draw[0]);
		v.draw[0] = 0;
	}
	while (v.draw[0] < v.draw[1])
	{
		v.texture[1] = (int)texture_pos % vars->textures[side].height;
		texture_pos += step;
		color = *(unsigned int *)(vars->textures[side].addr
				+ (v.texture[1] * vars->textures[side].line_length
					+ v.texture[0]
					* (vars->textures[side].bits_per_pixel / 8)));
		my_mlx_pixel_put(vars->mlx, x, v.draw[0], color);
		v.draw[0]++;
	}
}

/*
 * handles drawing a vertical textured stripe on the image
 */
void	draw_vertical_texture(t_vars *vars, int x_side[2],
		t_vectors v, double perp_wall_dist)
{
	double	wallx;

	if (x_side[1] == 0 || x_side[1] == 1)
		wallx = vars->pos_y + perp_wall_dist * v.ray[1];
	else
		wallx = vars->pos_x + perp_wall_dist * v.ray[0];
	wallx -= floor(wallx);
	v.texture[0] = (int)(wallx
			* (double)(vars->textures[x_side[1]].width));
	if ((x_side[1] == 0 || x_side[1] == 1) && v.ray[0] > 0)
		v.texture[0] = vars->textures[x_side[1]].width
			- v.texture[0] - 1;
	if ((x_side[1] == 2 || x_side[1] == 3) && v.ray[1] < 0)
		v.texture[0] = vars->textures[x_side[1]].width
			- v.texture[0] - 1;
	if (x_side[0] < 0 || x_side[0] >= S_WIDTH)
		return ;
	draw_loop(vars, x_side[0], v, x_side[1]);
}
