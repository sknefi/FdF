#include "fdf.h"

void	apply_offset(t_point_iso *p1, t_point_iso *p2, t_map *map)
{
	int		offset_x;
	int		offset_y;

	offset_x = (IMAGE_WIDTH - map->window_width) / 3;
	offset_y = (IMAGE_HEIGHT - map->window_height) / 2;
	p1->x += offset_x;
	p1->y += offset_y;
	p2->x += offset_x;
	p2->y += offset_y;
}

void	bresenham_line_loop(mlx_image_t *img, t_point_iso p1,
			t_point_iso p2, t_line_params params)
{
	int	e2;

	while (1)
	{
		safe_put_pixel(img, p1.x, p1.y, p1.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * params.err;
		if (e2 >= params.dy)
		{
			params.err += params.dy;
			p1.x += params.sx;
		}
		if (e2 <= params.dx)
		{
			params.err += params.dx;
			p1.y += params.sy;
		}
	}
}
