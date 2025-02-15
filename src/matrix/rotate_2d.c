#include "../fdf.h"

void	rotate_2d_left(t_app *app)
{
	app->transform->rotation += ROTATION_FACTOR;
	redraw_map(app);
}

void	rotate_2d_right(t_app *app)
{
	app->transform->rotation -= ROTATION_FACTOR;
	redraw_map(app);
}
