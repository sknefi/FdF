#include "fdf.h"
/**
 * @brief Adds a translation to the isometric point
 * @param pt The isometric point
 * @param tr The transformation structure
*/
static void	add_translation(t_point_pr *pt, t_transform *tr)
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
static void	add_rotation(t_point_pr *pt, t_transform *tr)
{
	int	prev_x;
	int	prev_y;

	prev_x = pt->x;
	prev_y = pt->y;
	pt->x = prev_x * cos(tr->rotation) - prev_y * sin(tr->rotation);
	pt->y = prev_x * sin(tr->rotation) + prev_y * cos(tr->rotation);
}

/**
 * @brief Projects a 3D point to isometric coordinates (2D)
 * @param pt The 3D point
*/
static t_point_pr	project_pt_to_iso(t_point *pt, t_transform *tr)
{
	double		scale;
	double		angle_iso;
	t_point_pr	pt_iso;

	angle_iso = 30 * (M_PI / 180.0);         // 30° in radians
	scale = 15.0 * tr->zoom;             // Scale factor multiplied by zoom
	// Compute basic isometric coordinates, scaled by the zoom factor.
	pt_iso.x = (int)(((pt->x - pt->y) * cos(angle_iso)) * scale);
	pt_iso.y = (int)((((pt->x + pt->y) * sin(angle_iso)) - pt->z) * scale);
	add_rotation(&pt_iso, tr);
	add_translation(&pt_iso, tr);
	pt_iso.z_val = pt->z;
	return (pt_iso);
}

static t_point_pr	project_pt_to_parallel(t_point *pt, t_transform *tr)
{
	t_point_pr	pt_par;

	pt_par.x = (int)(pt->x * tr->zoom);
	pt_par.y = (int)(pt->y * tr->zoom);
	add_translation(&pt_par, tr);
	pt_par.z_val = pt->z;
	return (pt_par);
}

t_point_pr	project_pt(t_point *pt, t_transform *tr)
{
	if (tr->projection == ISOMETRIC)
		return (project_pt_to_iso(pt, tr));	
	return (project_pt_to_parallel(pt, tr));
}