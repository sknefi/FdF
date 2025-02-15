#include "../fdf.h"

void	translate_x_left(t_app *app)
{
	app->transform->translation_x += TRANSLATION_FACTOR;
	redraw_map(app);
}

void	translate_x_right(t_app *app)
{
	app->transform->translation_x -= TRANSLATION_FACTOR;
	redraw_map(app);
}

void	translate_y_up(t_app *app)
{
	app->transform->translation_y += TRANSLATION_FACTOR;
	redraw_map(app);
}

void	translate_y_down(t_app *app)
{
	app->transform->translation_y -= TRANSLATION_FACTOR;
	redraw_map(app);
}
