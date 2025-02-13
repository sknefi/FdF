#include "fdf.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_K))
	// 	zoom_in();
	// if (mlx_is_key_down(mlx, MLX_KEY_L))
	// 	ft_putendl("Right arrow key is pressed");
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
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	(void)argv;
	if (argc != 2 || !is_filename_valid(argv[1]))
		return (ft_error("Usage - ./fdf <filename>.fdf"), EXIT_FAILURE);
	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FdF", TRUE);
	if (!mlx)
		ft_error(mlx_strerror(mlx_errno));
	img = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!img)
		ft_error(mlx_strerror(mlx_errno));
	map = parse_map(argv[1]);
	if (!map)
		ft_error("Map failed");
	draw_iso_map(map, img);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error(mlx_strerror(mlx_errno));
	mlx_resize_hook(mlx, resize_callback, map);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	cleanup(map, mlx, img);
	return (EXIT_SUCCESS);
}
