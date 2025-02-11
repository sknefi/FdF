#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	(void)argv;
	if (argc != 2 || !is_filename_valid(argv[1]))
		return (ft_error("Usage - ./fdf <filename>.fdf"), EXIT_FAILURE);

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", TRUE);
	if (!mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);

	map = parse_map(argv[1]);
	if (!map)
		return (ft_error("Map failed"), EXIT_FAILURE);
	
	draw_iso_map(map, img);
	
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
		
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);

	free_map(map);
	return (EXIT_SUCCESS);
}
