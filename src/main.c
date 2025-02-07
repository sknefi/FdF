#include "fdf.h"

void	display_line(mlx_image_t *img, int x, int y, int color)
{
	int		i;

	i = 0;
	while (i < x)
		mlx_put_pixel(img, i++, y, color);
}

int		main(void)
{
	mlx_t	*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", TRUE);
	if (!mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	display_line(img, 100, 150, 0xFF0000FF);
	mlx_put_pixel(img, 80, 400, 0xFF0000FF);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
