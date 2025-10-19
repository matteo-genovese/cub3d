#include "cub3d.h"
#include <string.h>

//FUNZIONE INUTILE SOLTANTO PER TESTARE LA MAPPA DA ARRAY 2D A CHAR**
void load_map(t_vars *vars, int src[mapWidth][mapHeight])
{
	int r, c;

    vars->map = (char **)malloc(sizeof(char *) * mapWidth);
    for (r = 0; r < mapWidth; ++r)
    {
        vars->map[r] = (char *)malloc(sizeof(char) * mapHeight);
        for (c = 0; c < mapHeight; ++c)
        {
            vars->map[r][c] = (char)src[r][c];
		}
	}
}
