#include "cub3d.h"
#include <string.h>

#define mapWidth 24
#define mapHeight 24

int		worldMap[mapWidth][mapHeight] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0,
			0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1}, {1, 0, 0,
			0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1,
			0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0,
			1}, {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1}, {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0,
			3, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
										{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
											{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
											1}};

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

void	draw_line(t_mlx_win *mlx_win, int beginX, int beginY, int endX,
		int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	if (pixels == 0)
		return ;
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(mlx_win, (int)pixelX, (int)pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	render(t_vars *vars)
{
	int			i;
	int			hit;
	int			side;
	int			map[2];
	int			step[2];
	double		position[2];
	double		camera[2];
	double		ray[2];
	double		dir[2];
	double		plane[2];
	double		sidedist[2];
	double		deltadist[2];
	t_mlx_win	*mlx;
		double perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			drawEnd;
	int			tile;
		int color;
	int			r;
	int			g;
	int			b;

	mlx = vars->mlx;
	i = 0;
	position[0] = vars->pos_x;
	position[1] = vars->pos_y;
	dir[0] = vars->dir_x;
	dir[1] = vars->dir_y;
	plane[0] = vars->plane[0];
	plane[1] = vars->plane[1];
	sidedist[0] = 0;
	sidedist[1] = 0;
	hit = 0;
	/* clear image buffer for a fresh frame */
	if (mlx && mlx->addr)
		memset(mlx->addr, 0, S_HEIGHT * mlx->line_length);
	while (i < S_WIDTH)
	{
		hit = 0;
		camera[0] = 2 * i / (double)S_WIDTH - 1;
		ray[0] = dir[0] + plane[0] * camera[0];
		ray[1] = dir[1] + plane[1] * camera[0];
		map[0] = (int)position[0];
		map[1] = (int)position[1];
		deltadist[0] = fabs(1 / ray[0]);
		if (ray[0] == 0)
			deltadist[0] = 1e30;
		deltadist[1] = fabs(1 / ray[1]);
		if (ray[1] == 0)
			deltadist[1] = 1e30;
		if (ray[0] < 0)
		{
			step[0] = -1;
			sidedist[0] = (position[0] - map[0]) * deltadist[0];
		}
		else
		{
			step[0] = 1;
			sidedist[0] = (-position[0] + map[0] + 1) * deltadist[0];
		}
		if (ray[1] < 0)
		{
			step[1] = -1;
			sidedist[1] = (position[1] - map[1]) * deltadist[1];
		}
		else
		{
			step[1] = 1;
			sidedist[1] = (-position[1] + map[1] + 1) * deltadist[1];
		}
		while (hit == 0)
		{
			if (sidedist[0] < sidedist[1])
			{
				sidedist[0] += deltadist[0];
				map[0] += step[0];
				side = 'N';
				if (step[0] > 0)
					side = 'S';
			}
			else
			{
				sidedist[1] += deltadist[1];
				map[1] += step[1];
				side = 'E';
				if (step[1] > 0)
					side = 'W';
			}
			if (worldMap[map[0]][map[1]] > 0)
				hit = 1;
		}
		if (side == 'N' || side == 'S')
			perp_wall_dist = (sidedist[0] - deltadist[0]);
		else
			perp_wall_dist = (sidedist[1] - deltadist[1]);
		line_height = (int)(S_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + S_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		drawEnd = line_height / 2 + S_HEIGHT / 2;
		if (drawEnd >= S_HEIGHT)
			drawEnd = S_HEIGHT - 1;
		switch (side)
		{
		case 'N':
			color = 0xFF0000;
			break ; /* red */
		case 'S':
			color = 0x00FF00;
			break ; /* green */
		case 'E':
			color = 0x0000FF;
			break ; /* blue */
		case 'W':
			color = 0xFFFF00;
			break ; /* yellow */
		default:
			color = 0xFFFFFF;
			break ; /* white */
		}
		/* darken color for y-side hits to give visual depth */
		draw_line(mlx, i, draw_start, i, drawEnd, color);
		i++;
	}
	/* put the composed image to the window once per frame */
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
