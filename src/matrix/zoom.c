#include "../fdf.h"

void	zoom_in(t_app *app)
{
	app->transform->zoom += ZOOM_FACTOR;
	redraw_map(app);
}

void	zoom_out(t_app *app)
{
	app->transform->zoom -= ZOOM_FACTOR;
	redraw_map(app);
}
