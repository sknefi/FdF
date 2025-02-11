#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height_y_axis)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	free(map);
}
