#include "fdf.h"

void	apply_offset(t_point_iso *p1, t_point_iso *p2, t_map *map)
{
	(void)map;
	p1->x += X_OFFSET;
	p1->y += Y_OFFSET;
	p2->x += X_OFFSET;
	p2->y += Y_OFFSET;
	// p1->x += map->window_width / 2;
	// p1->y += map->window_height / 4;
	// p2->x += map->window_width / 2;
	// p2->y += map->window_height / 4;
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
