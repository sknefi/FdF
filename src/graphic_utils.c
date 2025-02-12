#include "fdf.h"

void	apply_offset(t_point_iso *p1, t_point_iso *p2, t_map *map)
{
	int		offset_x;
	int		offset_y;

	offset_x = (int)(IMAGE_WIDTH - map->window_width) / 1.5;
	offset_y = (int)(IMAGE_HEIGHT - map->window_height) / 2;
	p1->x += offset_x;
	p1->y += offset_y;
	p2->x += offset_x;
	p2->y += offset_y;
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	calc_color(t_map *map, t_line_params *line)
{
	int		val;
	int		alpha;
	int		base_color;
	float	percent;

	val = 31;
	base_color = DEFAULT_COLOR;
	if (line->p1->z_val > line->p2->z_val)
		percent = (float)(line->p1->z_val - map->min_z) / (map->max_z - map->min_z);
	else
		percent = (float)(line->p2->z_val - map->min_z) / (map->max_z - map->min_z);
	alpha = val + (int)(percent * (255 - val));
	if (alpha > 255)
		alpha = 255;
	if (alpha < val)
		alpha = val;
	return (base_color << 8) | (alpha & 0xFF);
}
