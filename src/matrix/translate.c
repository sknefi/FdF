#include "../fdf.h"

void	translate_x_left(t_app *app)
{
	app->transform->translation_x += TRANSLATION_FACTOR;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_pr_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}

void	translate_x_right(t_app *app)
{
	app->transform->translation_x -= TRANSLATION_FACTOR;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_pr_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}

void	translate_y_up(t_app *app)
{
	app->transform->translation_y += TRANSLATION_FACTOR;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_pr_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}

void	translate_y_down(t_app *app)
{
	app->transform->translation_y -= TRANSLATION_FACTOR;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_pr_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}
