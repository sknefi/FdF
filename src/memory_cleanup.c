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

void	cleanup(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	free_map(map);
}

void	clean_app(t_app *app)
{
	mlx_delete_image(app->mlx, app->img);
	mlx_terminate(app->mlx);
	free_map(app->map);
	free(app->transform);
}
