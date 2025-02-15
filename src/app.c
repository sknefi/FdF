#include "fdf.h"

/**
 * @brief Initializes the transform structure with default values
*/
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

/**
 * @brief Creates a map structure and fills it with the values from the file
 * @param filename The filename
*/
static t_map	*parse_map(char *filename)
{
	int			nl_count;
	t_map		*map;

	nl_count = new_line_count(filename);
	if (nl_count == -1 || nl_count == 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width_x_axis = 0;
	map->height_y_axis = nl_count;
	map->window_width = WINDOW_WIDTH;
	map->window_height = WINDOW_HEIGHT;
	map->start_color = START_COLOR;
	map->end_color = END_COLOR;
	map->matrix = (t_point **)malloc(sizeof(t_point *) * nl_count);
	if (!map->matrix)
		return (free(map), NULL);
	if (fill_matrix(map, filename) < 0)
		return (free(map->matrix), free(map), NULL);
	find_min_max_in_matrix(map);
	return (map);
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
