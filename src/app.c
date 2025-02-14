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
	return (transform);
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