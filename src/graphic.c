#include "fdf.h"

void	safe_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	draw_line(t_map *map, mlx_image_t *img, t_point_iso p1, t_point_iso p2)
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
	bresenham_line_loop(img, p1, p2, line);
}
