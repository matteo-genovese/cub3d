#ifndef CUB3D_H
# define CUB3D_H

# define S_WIDTH 1080
# define S_HEIGHT 720
# define FPS 30
#define mapWidth 24
#define mapHeight 24

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
#include <sys/time.h>
# include "libft.h"

typedef struct s_mlx_win
{
	void	*mlx;
	void	*win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}				t_mlx_win;

typedef struct keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keys;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_vars
{
	t_mlx_win	*mlx;
	t_image		textures[4];
	t_keys		keys;
	char		**map;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rot_speed;
	double		plane[2];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}				t_vars;

//TODO VARIABILE GLOBALE STACCA TUTTO

extern int worldMap[mapWidth][mapHeight];

void	init(t_mlx_win *vars);
void	move(t_vars *vars);
void	render(t_vars *vars);
void	hooks(t_vars *vars);
void	draw_line(t_mlx_win *mlx_win, int beginX, int beginY, int endX, int endY, int color);
void	my_mlx_pixel_put(t_mlx_win *mlx_win, int x, int y, int color);
void	load_map(t_vars *vars, int src[mapWidth][mapHeight]);

#endif
