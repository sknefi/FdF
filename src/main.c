#include "fdf.h"

/**
 * @brief Handles the key presses
 * @param param The app structure
*/
static void	ft_hook(void *param)
{
	t_app	*app;

	app = param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_K))
		zoom_in(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_L))
		zoom_out(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_A))
		translate_x_left(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_D))
		translate_x_right(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_W))
		translate_y_up(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_S))
		translate_y_down(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
		rotate_2d_left(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_E))
		rotate_2d_right(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_B))
		change_projection(app, ISOMETRIC);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_N))
		change_projection(app, PARALLEL);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_R))
		reset_map(app);
	else if (mlx_is_key_down(app->mlx, MLX_KEY_M))
		change_colors(app, 0x81F4E1FF, 0x00000000);
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
		return (clean_app(&app), ft_error("Failed to update the app"), 1);
	redraw_map(&app);
	mlx_loop_hook(app.mlx, ft_hook, &app);
	mlx_loop(app.mlx);
	clean_app(&app);
	return (EXIT_SUCCESS);
}
