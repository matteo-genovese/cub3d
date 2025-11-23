/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:47:39 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:48:00 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
