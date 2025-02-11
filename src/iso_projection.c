#include "fdf.h"

/**
 * @brief Projects a 3D point to isometric coordinates (2D)
 * @param pt The 3D point
*/
static t_point_iso	project_pt_to_iso(t_point pt)
{
	double		angle;
	double		scale;
	t_point_iso	pt_iso;

	angle = 30 * (M_PI / 180.0);  // 30° in radians
	scale = 40.0;  // Increase this value to scale up the projection
	// Compute basic isometric coordinates
	pt_iso.x = (int)(((pt.x - pt.y) * cos(angle)) * scale);
	pt_iso.y = (int)((((pt.x + pt.y) * sin(angle)) - pt.z) * scale);
	pt_iso.color = DEFAULT_COLOR;
	return (pt_iso);
}

void	draw_iso_map(t_map *map, mlx_image_t *img)
{
	int			i;
	int			j;
	t_point_iso	p1;

	i = 0;
	while (i < map->height_y_axis)
	{
		j = 0;
		while (j < map->width_x_axis)
		{
			p1 = project_pt_to_iso(map->matrix[i][j]);
			// If there is a point to the right, draw a line to it.
			if (j + 1 < map->width_x_axis)
				draw_line(img, p1, project_pt_to_iso(map->matrix[i][j + 1]));
			// If there is a point below, draw a line to it.
			if (i + 1 < map->height_y_axis)
				draw_line(img, p1, project_pt_to_iso(map->matrix[i + 1][j]));
			j++;
		}
		i++;
	}
}
