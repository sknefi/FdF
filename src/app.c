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
	transform->projection = ISOMETRIC;
	return (transform);
}

void	change_projection(t_app *app, t_projection_type projection)
{
	app->transform->projection = projection;
	redraw_map(app);
}

void	reset_map(t_app *app)
{
	app->transform->rotation = 0;
	app->transform->zoom = 1;
	app->transform->translation_x = 0;
	app->transform->translation_y = 0;
	app->transform->projection = ISOMETRIC;
	redraw_map(app);
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
