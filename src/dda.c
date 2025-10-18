#include "cub3d.h"
#include <string.h>



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

void	draw_vertical_texture(t_mlx_win *mlx_win, int X, int beginY,
		int endY, t_image texture, int textureX)
{
	double step;
	double texturePos;
	int textureY;
	int y;
	int color;
	if (X < 0 || X >= S_WIDTH)
		return ;


	step = 1.0 * texture.height / (endY - beginY);
	texturePos = (beginY - S_HEIGHT / 2 + (endY - beginY) / 2) * step;
	if (endY >= S_HEIGHT)
		endY = S_HEIGHT - 1;
	if (beginY < 0)
	{
		texturePos = step * (-beginY);
		beginY = 0;
	}
	y =  beginY;
	while (y < endY)
	{
		textureY = (int)texturePos & (texture.height - 1);
		texturePos += step;
		color = *(unsigned int *)(texture.addr + (textureY * texture.line_length
					+ textureX * (texture.bits_per_pixel / 8)));
		my_mlx_pixel_put(mlx_win, X, y, color);
		y++;
	}
}

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

void	vectors_setup(t_vars *vars, t_vectors *v, int i)
{
	v->camera[0] = 2 * i / (double)S_WIDTH - 1;
	v->ray[0] = vars->dir_x + vars->plane[0] * v->camera[0];
	v->ray[1] = vars->dir_y + vars->plane[1] * v->camera[0];
	v->map[0] = (int)vars->pos_x;
	v->map[1] = (int)vars->pos_y;
	v->deltadist[0] = fabs(1 / v->ray[0]);
	if (v->ray[0] == 0.0)
		v->deltadist[0] = 1e30;
	v->deltadist[1] = fabs(1 / v->ray[1]);
	if (v->ray[1] == 0.0)
		v->deltadist[1] = 1e30;
	if (v->ray[0] < 0)
	{
		v->step[0] = -1;
		v->sidedist[0] = (vars->pos_x - v->map[0]) * v->deltadist[0];
	}
	else
	{
		v->step[0] = 1;
		v->sidedist[0] = (-vars->pos_x + v->map[0] + 1) * v->deltadist[0];
	}
	if (v->ray[1] < 0)
	{
		v->step[1] = -1;
		v->sidedist[1] = (vars->pos_y - v->map[1]) * v->deltadist[1];
	}
	else
	{
		v->step[1] = 1;
		v->sidedist[1] = (-vars->pos_y + v->map[1] + 1) * v->deltadist[1];
	}
}

void	render(t_vars *vars)
{
    int			i;
    int			hit;
    int			side;
    t_vectors	v;
    double		perp_wall_dist;
    int			line_height;
    int			draw_start;
    int			drawEnd;
	double 		wallX;

    if (!vars)
        return ;
    i = 0;
    v.sidedist[0] = 0.0;
    v.sidedist[1] = 0.0;
    hit = 0;
    image_startup(vars);
    i = 0;
    while (i < S_WIDTH)
    {
        hit = 0;
		vectors_setup(vars, &v, i);
        while (hit == 0)
        {
            if (v.sidedist[0] < v.sidedist[1])
            {
                v.sidedist[0] += v.deltadist[0];
                v.map[0] += v.step[0];
                side = 0;
                if (v.step[0] > 0)
                    side = 1;
            }
            else
            {
                v.sidedist[1] += v.deltadist[1];
                v.map[1] += v.step[1];
                side = 2;
                if (v.step[1] > 0)
                    side = 3;
            }
            if (worldMap[v.map[0]][v.map[1]] > 0)
                hit = 1;
        }
        if (side == 0 || side == 1)
            perp_wall_dist = (v.sidedist[0] - v.deltadist[0]);
        else
            perp_wall_dist = (v.sidedist[1] - v.deltadist[1]);
        if (perp_wall_dist == 0.0)
            perp_wall_dist = 1e-6;
        line_height = (int)(S_HEIGHT / perp_wall_dist);
        draw_start = -line_height / 2 + S_HEIGHT / 2;
        drawEnd = line_height / 2 + S_HEIGHT / 2;
		
		if (side == 0 || side == 1)
			wallX = vars->pos_y + perp_wall_dist * v.ray[1];
		else
			wallX = vars->pos_x + perp_wall_dist * v.ray[0];
		wallX -= floor(wallX);
		int texture_x = (int)(wallX * (double)(vars->textures[side].width));
		if ((side == 0 || side == 1) && v.ray[0] > 0)
			texture_x += vars->textures[side].width - texture_x - 1;
		if ((side == 2 || side == 3) && v.ray[1] < 0)
			texture_x = vars->textures[side].width - texture_x - 1;
		draw_vertical_texture(vars->mlx, i, draw_start, drawEnd, vars->textures[side], texture_x);
        i++;
    }
    mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->mlx->img, 0, 0);
}
