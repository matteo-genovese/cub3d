#include "cub3d.h"

int ft_exit(int code, char *message, int exit_code)
{
	if (code == 1)
		printf("Error: %s\n", message);
	exit(exit_code);
}
