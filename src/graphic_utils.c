#include "fdf.h"

void	apply_offset(t_point_pr *p1, t_point_pr *p2, t_map *map)
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

/**
 * @brief Puts bytes in the right order for the pixel
 * @param r The red byte
 * @param g The green byte
 * @param b The blue byte
 * @param a The alpha byte
*/
static int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief Interpolates between two colors, given a percentage
 * @param start The start color
 * @param end The end color
 * @param t The percentage
*/
static int	interpolate_color(int start, int end, float t)
{
	t_rgba	s;
	t_rgba	e;

	s.r = (start >> 24) & 0xFF;
	s.g = (start >> 16) & 0xFF;
	s.b = (start >> 8) & 0xFF;
	s.a = start & 0xFF;
	e.r = (end >> 24) & 0xFF;
	e.g = (end >> 16) & 0xFF;
	e.b = (end >> 8) & 0xFF;
	e.a = end & 0xFF;
	return (ft_pixel(
		s.r + (int)((e.r - s.r) * t),
		s.g + (int)((e.g - s.g) * t),
		s.b + (int)((e.b - s.b) * t),
		s.a + (int)((e.a - s.a) * t)
	));
}

int	calc_color(t_map *map, t_line_params *line)
{
	int		z_avg;
	int		end_color;
	int		start_color;
	float	percent;

	start_color = START_COLOR;
	end_color   = END_COLOR;
	z_avg = (line->p1->z_val + line->p2->z_val) / 2;
	percent = (float)(z_avg - map->min_z) / (map->max_z - map->min_z);
	if (percent < 0)
		percent = 0;
	if (percent > 1)
		percent = 1;
	return (interpolate_color(start_color, end_color, percent));
}
