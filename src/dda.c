#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color) {
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;
    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
    deltaX /= pixels;
    deltaY /= pixels;

    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels) {
        mlx_pixel_put(mlx, win, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
}

void	render(t_mlx_win *mlx)
{
  int	  i;
  int	  hit;
  int	  side;
  int	  map[2];
  int	  step[2];
  double  position[2];
  double  camera[2];
  double  ray[2];
  double  dir[2];
  double  plane[2];
  double  times[2];
  double  sidedist[2];
  double  deltadist[2];

  i = 0;
  position[0] = 22;
  position[1] = 12;
  dir[0] = -1;
  dir[1] = 0;
  plane[0] = 0;
  plane[1] = 0.66;
  times[0] = 0;
  times[1] = 0;
  hit = 0;
  while ( i < S_WIDTH)
  {
    hit = 0;
    camera[0] = 2 * i / (double) S_WIDTH - 1;
    ray[0] = dir[0] + plane[0] * camera[0];
    ray[1] = dir[1] + plane[1] * camera[0];
    map[0] = (int)position[0];
    map[1] = (int)position[1];
    deltadist[0] = fabs(1/ray[0]);
    if (ray[0] == 0)
      deltadist[0] = 1e30;
    deltadist[1] = fabs(1/ray[1]);
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
      sidedist[0] = (- position[0] + map[0] + 1) * deltadist[0];
    }
    if (ray[1] < 0)
    {
      step[1] = -1;
      sidedist[1] = (position[1] - map[1]) * deltadist[1];
    }
    if (ray[0] < 0)
    {
      step[1] = 1;
      sidedist[1] = (- position[1] + map[1] + 1) * deltadist[1];
    }
    while (hit == 0)
    {
      if (sidedist[0] < sidedist[1])
      {
	sidedist[0] += deltadist[0];
	map[0] += step[0];
	side = 0;
      }
      else
    {
	  sidedist[1] += deltadist[1];
	map[1] += step[1];
	side = 1;
      }
	if (worldMap[map[0]][map[1]] > 0) hit = 1;
    }
    double  perp_wall_dist;
    if (side == 0)
      perp_wall_dist = (sidedist[0] - deltadist[0]);
    else
      perp_wall_dist = (sidedist[1] - deltadist[1]);
    int	line_height  = (int)(S_HEIGHT / perp_wall_dist);

    int draw_start = -line_height/2 + S_HEIGHT/2;
    if(draw_start < 0)draw_start = 0;
    int drawEnd = line_height / 2 + S_HEIGHT / 2;
    if(drawEnd >= S_HEIGHT)drawEnd = S_HEIGHT - 1;

    draw_line(mlx->mlx, mlx->win, i, draw_start , i , drawEnd, 0xFFFFFF);
    i++;
  }
}

