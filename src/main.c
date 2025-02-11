#include "fdf.h"

// void	display_line(mlx_image_t *img, int x, int y, int color)
// {
// 	int	i;

// 	i = 0;
// 	while (i < x)
// 		mlx_put_pixel(img, i++, y, color);
// }

int	is_filename_valid(char *filename)
{
	size_t	len_filename;

	len_filename = ft_strlen(filename);
	if (len_filename < 5)
		return (FALSE);
	len_filename -= 4;
	if (ft_strncmp(filename + len_filename, ".fdf", 4) != 0)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_map		*map;
	// mlx_t		*mlx;
	// mlx_image_t	*img;

	(void)argv;
	if (argc != 2 || !is_filename_valid(argv[1]))
		return (ft_error("Usage - ./fdf <filename>.fdf"), EXIT_FAILURE);
	// mlx = mlx_init(WIDTH, HEIGHT, "FdF", TRUE);
	// if (!mlx)
	// 	return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	// img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// if (!img)
	// 	return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);

	map = parse_map(argv[1]);
	if (!map)
		return (ft_error("Map failed"), EXIT_FAILURE);
	print_map(map);
	// display_line(img, 100, 150, 0xFF0000FF);
	// mlx_put_pixel(img, 80, 400, 0xFF0000FF);
	
	// if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	// 	return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	// mlx_loop(mlx);
	// mlx_delete_image(mlx, img);
	// mlx_terminate(mlx);
	free_map(map);
	return (EXIT_SUCCESS);
}
