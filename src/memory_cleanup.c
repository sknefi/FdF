#include "fdf.h"

/**
 * @brief Free the map matrix and the map structure
 * @param map The map structure
*/
static void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->height_y_axis)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	free(map);
}

void	clean_app(t_app *app)
{
	mlx_delete_image(app->mlx, app->img);
	mlx_terminate(app->mlx);
	free_map(app->map);
	free(app->transform);
}
