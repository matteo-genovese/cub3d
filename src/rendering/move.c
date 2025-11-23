/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:45:17 by fde-sist          #+#    #+#             */
/*   Updated: 2025/11/23 17:52:31 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_move(t_vars *vars, double newX, double newY)
{
	return (vars->map[(int)(newX)][(int)(newY)] != '1');
}

void	rotate_view(t_vars *vars, double angle)
{
	double	old_dir[2];
	double	old_plane[2];
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	old_dir[0] = vars->dir_x;
	old_dir[1] = vars->dir_y;
	old_plane[0] = vars->plane[0];
	old_plane[1] = vars->plane[1];
	vars->dir_x = old_dir[0] * c - old_dir[1] * s;
	vars->dir_y = old_dir[0] * s + old_dir[1] * c;
	vars->plane[0] = old_plane[0] * c - old_plane[1] * s;
	vars->plane[1] = old_plane[0] * s + old_plane[1] * c;
}

void	move_w_s(t_vars *vars)
{
	if (vars->keys.w)
	{
		if (is_valid_move(vars, vars->pos_x + vars->dir_x
				* vars->move_speed, vars->pos_y
				+ vars->dir_y * vars->move_speed))
		{
			vars->pos_x += vars->dir_x * vars->move_speed;
			vars->pos_y += vars->dir_y * vars->move_speed;
		}
	}
	if (vars->keys.s)
	{
		if (is_valid_move(vars, vars->pos_x - vars->dir_x
				* vars->move_speed, vars->pos_y
				- vars->dir_y * vars->move_speed))
		{
			vars->pos_x -= vars->dir_x * vars->move_speed;
			vars->pos_y -= vars->dir_y * vars->move_speed;
		}
	}
}

void	move_a_d(t_vars *vars)
{
	if (vars->keys.a)
	{
		if (is_valid_move(vars, vars->pos_x - vars->dir_y
				* vars->move_speed, vars->pos_y
				+ vars->dir_x * vars->move_speed))
		{
			vars->pos_x -= vars->dir_y * vars->move_speed;
			vars->pos_y += vars->dir_x * vars->move_speed;
		}
	}
	if (vars->keys.d)
	{
		if (is_valid_move(vars, vars->pos_x + vars->dir_y
				* vars->move_speed, vars->pos_y
				- vars->dir_x * vars->move_speed))
		{
			vars->pos_x += vars->dir_y * vars->move_speed;
			vars->pos_y -= vars->dir_x * vars->move_speed;
		}
	}
}

void	move(t_vars *vars)
{
	move_w_s(vars);
	move_a_d(vars);
	if (vars->keys.left)
		rotate_view(vars, vars->rot_speed);
	if (vars->keys.right)
		rotate_view(vars, -vars->rot_speed);
	render(vars);
}
