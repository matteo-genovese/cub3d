#ifndef CUB3D_H
# define CUB3D_H

# define S_WIDTH 1080
# define S_HEIGHT 720

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct s_mlx_win
{
	void	*mlx;
	void	*win;
}				t_mlx_win;

void	init(t_mlx_win *vars);
void	render(t_mlx_win *vars);
void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);

#endif
