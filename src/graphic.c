#include "fdf.h"

/**
 * @brief Safely put a pixel on the image, 
 * checking if the coordinates are within bounds
 * @param img The image
 * @param x The x coordinate
 * @param y The y coordinate
 * @param color The color
*/
static void	safe_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT)
		return ;
	mlx_put_pixel(img, x, y, color);
}

/**
 * @brief Draws a line between two projected points, Bresenham's line algorithm
 * @param img The image
 * @param line The line parameters
*/
static void	bresenham_line_loop(mlx_image_t *img,
	t_map *map, t_line_params *line)
{
	int	e2;

	while (1)
	{
		safe_put_pixel(img, line->p1->x, line->p1->y, calc_color(map, line));
		if (line->p1->x == line->p2->x && line->p1->y == line->p2->y)
			break ;
		e2 = 2 * line->err;
		if (e2 >= line->dy)
		{
			line->err += line->dy;
			line->p1->x += line->sx;
		}
		if (e2 <= line->dx)
		{
			line->err += line->dx;
			line->p1->y += line->sy;
		}
	}
}

void	draw_line(t_map *map, mlx_image_t *img, t_pt_pr p1, t_pt_pr p2)
{
	t_line_params	line;

	apply_offset(&p1, &p2, map);
	line.dx = abs(p2.x - p1.x);
	if (p1.x < p2.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -abs(p2.y - p1.y);
	if (p1.y < p2.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.p1 = &p1;
	line.p2 = &p2;
	bresenham_line_loop(img, map, &line);
}

void	redraw_map(t_app *app)
{
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	draw_pr_map(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		clean_app(app);
		ft_error(mlx_strerror(mlx_errno));
	}
}
