#include "../fdf.h"

void	rotate_3d_x_left(t_app *app)
{
	app->transform->rotation_x += RF_X;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_iso_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}

void	rotate_3d_x_right(t_app *app)
{
	app->transform->rotation_x -= RF_X;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_iso_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
}