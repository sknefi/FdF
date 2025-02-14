#include "fdf.h"

/**
 * @brief Projects a 3D point to isometric coordinates (2D)
 * @param pt The 3D point
*/
static t_point_iso	project_pt_to_iso(t_point pt, t_transform *tr)
{
	double		angle;
	double		scale;
	t_point_iso	pt_iso;

	angle = 30 * (M_PI / 180.0);         // 30° in radians
	scale = 15.0 * tr->zoom;             // Scale factor multiplied by zoom

	// Compute basic isometric coordinates, scaled by the zoom factor.
	pt_iso.x = (int)(((pt.x - pt.y) * cos(angle)) * scale);
	pt_iso.y = (int)((((pt.x + pt.y) * sin(angle)) - pt.z) * scale);

	// Apply translation offsets from the transformation structure.
	pt_iso.x += tr->translation_x;
	pt_iso.y += tr->translation_y;

	pt_iso.z_val = pt.z;               // Preserve the original z value
	pt_iso.color = DEFAULT_COLOR;      // Set the default color
	return (pt_iso);
}


void	draw_iso_map(t_app *app)
{
	int			i;
	int			j;
	t_point_iso	p1;

	i = 0;
	while (i < app->map->height_y_axis)
	{
		j = 0;
		while (j < app->map->width_x_axis)
		{
			p1 = project_pt_to_iso(app->map->matrix[i][j], app->transform);
			if (j + 1 < app->map->width_x_axis)
				draw_line(app->map, app->img, p1, project_pt_to_iso(app->map->matrix[i][j + 1], app->transform));
			if (i + 1 < app->map->height_y_axis)
				draw_line(app->map, app->img, p1, project_pt_to_iso(app->map->matrix[i + 1][j], app->transform));
			j++;
		}
		i++;
	}
}
