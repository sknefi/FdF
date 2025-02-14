#include "fdf.h"

static t_transform	*init_transform(void)
{
	t_transform		*transform;

	transform = (t_transform *)malloc(sizeof(t_transform));
	if (!transform)
		return (NULL);
	transform->translation_x = 0;
	transform->translation_y = 0;
	transform->zoom = 1.0;
	transform->rotation = 0.0;
	transform->rotation_x = 0.0;
	transform->rotation_y = 0.0;
	transform->rotation_z = 0.0;
	transform->projection = ISOMETRIC;
	return (transform);
}

void	change_projection(t_app *app, t_projection_type projection)
{
	app->transform->projection = projection;
	ft_printf("%d\n", app->transform->projection);
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_iso_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}

int	update_app(t_app *app, char *filename)
{
	app->map = parse_map(filename);
	if (!app->map)
		return (-1);
	app->transform = init_transform();
	if (!app->transform)
		return (-1);
	return (1);
}