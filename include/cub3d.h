#ifndef CUB3D_H
# define CUB3D_H

# define S_WIDTH 1080
# define S_HEIGHT 720

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
#include <sys/time.h>

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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_vars
{
	t_mlx_win	*mlx;
	t_image		textures[4];
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rot_speed;
	double		plane[2];
}				t_vars;

void	init(t_mlx_win *vars);
void	render(t_vars *vars);
void	hooks(t_vars *vars);
void	draw_line(t_mlx_win *mlx_win, int beginX, int beginY, int endX, int endY, int color);
void	my_mlx_pixel_put(t_mlx_win *mlx_win, int x, int y, int color);

#endif
