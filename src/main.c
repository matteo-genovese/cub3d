#include "cub3d.h"

int main() {
	t_mlx_win	mlx;

	mlx.mlx = NULL;
	mlx.win = NULL;
	init(&mlx);

	mlx_loop(mlx.mlx);
	return 0;
}
