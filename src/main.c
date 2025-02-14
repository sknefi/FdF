#include "fdf.h"

void	ft_hook(void *param)
{
	t_app	*app;

	app = param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (mlx_is_key_down(app->mlx, MLX_KEY_K))
		zoom_in(app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_L))
		zoom_out(app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_A))
		translate_x_left(app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_D))
		translate_x_right(app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
		translate_y_up(app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
		translate_y_down(app);
}

void	resize_callback(int32_t width, int32_t height, void *param)
{
	t_map		*map;

	map = (t_map *)param;
	map->window_width = width;
	map->window_height = height;
	ft_printf("Window resized: %d x %d\n", width, height);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2 || !is_filename_valid(argv[1]))
		return (ft_error("Usage - ./fdf <filename>.fdf"), EXIT_FAILURE);
	app.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FdF", TRUE);
	if (!app.mlx)
		ft_error(mlx_strerror(mlx_errno));
	app.img = mlx_new_image(app.mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!app.img)
		ft_error(mlx_strerror(mlx_errno));
	if (update_app(&app, argv[1]) < 0)
		return (clean_app(&app),ft_error("Failed to update the app"), EXIT_FAILURE);
	draw_iso_map(&app);
	if (mlx_image_to_window(app.mlx, app.img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
	mlx_resize_hook(app.mlx, resize_callback, app.map);
	mlx_loop_hook(app.mlx, ft_hook, &app);
	mlx_loop(app.mlx);
	clean_app(&app);
	return (EXIT_SUCCESS);
}
