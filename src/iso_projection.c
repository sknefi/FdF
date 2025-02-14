#include "fdf.h"
/**
 * @brief Adds a translation to the isometric point
 * @param pt The isometric point
 * @param tr The transformation structure
*/
static void	add_translation(t_point_iso *pt, t_transform *tr)
{
	pt->x += tr->translation_x;
	pt->y += tr->translation_y;
}

/**
 * @brief Adds a rotation to the isometric point
 * Rotation matrix in 2D:
 * | cos(θ) -sin(θ) |
 * | sin(θ)  cos(θ) |
 * @param pt The isometric point
 * @param tr The transformation structure
*/
static void	add_rotation(t_point_iso *pt, t_transform *tr)
{
	int	prev_x;
	int	prev_y;

	prev_x = pt->x;
	prev_y = pt->y;
	pt->x = prev_x * cos(tr->rotation) - prev_y * sin(tr->rotation);
	pt->y = prev_x * sin(tr->rotation) + prev_y * cos(tr->rotation);
}

// Rotate a 3D point around the X, Y, and Z axes.
static t_point_iso	rotate_3d(t_point_iso pt, t_transform *tr)
{
	double			rad_x;
	double			rad_y;
	double			rad_z;
	t_point_iso		rotated;
	t_point_iso		temp;

	// Convert rotation angles from degrees to radians.
	rad_x = tr->rotation_x * (M_PI / 180.0);
	rad_y = tr->rotation_y * (M_PI / 180.0);
	rad_z = tr->rotation_z * (M_PI / 180.0);
	// Rotate around the X-axis.
	rotated.x = pt.x;
	rotated.y = pt.y * cos(rad_x) - pt.z_val * sin(rad_x);
	rotated.z_val = pt.y * sin(rad_x) + pt.z_val * cos(rad_x);
	// Rotate around the Y-axis.
	temp.x = rotated.x * cos(rad_y) + rotated.z_val * sin(rad_y);
	temp.y = rotated.y;
	temp.z_val = -rotated.x * sin(rad_y) + rotated.z_val * cos(rad_y);
	rotated = temp;
	// Rotate around the Z-axis.
	temp.x = rotated.x * cos(rad_z) - rotated.y * sin(rad_z);
	temp.y = rotated.x * sin(rad_z) + rotated.y * cos(rad_z);
	temp.z_val = rotated.z_val;
	rotated = temp;
	return (rotated);
}



/**
 * @brief Projects a 3D point to isometric coordinates (2D)
 * @param pt The 3D point
*/
static t_point_iso	project_pt_to_iso(t_point pt, t_transform *tr)
{
	double		scale;
	double		angle_iso;
	t_point_iso	pt_iso;

	angle_iso = 30 * (M_PI / 180.0);         // 30° in radians
	scale = 15.0 * tr->zoom;             // Scale factor multiplied by zoom

	
	// Compute basic isometric coordinates, scaled by the zoom factor.
	pt_iso.x = (int)(((pt.x - pt.y) * cos(angle_iso)) * scale);
	pt_iso.y = (int)((((pt.x + pt.y) * sin(angle_iso)) - pt.z) * scale);
	pt_iso = rotate_3d(pt_iso, tr);
	add_rotation(&pt_iso, tr);
	add_translation(&pt_iso, tr);
	pt_iso.z_val = pt.z;
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
