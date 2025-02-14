#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <math.h> 
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include "../libft_divinus/libft.h"

// pr - projected
// pt - point
// iso - isometric
// par - parallel

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 800
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 600
# endif

# ifndef IMAGE_WIDTH
#  define IMAGE_WIDTH 1920
# endif

# ifndef IMAGE_HEIGHT
#  define IMAGE_HEIGHT 1080
# endif

# define TITLE "FdF"
# define TRUE 1
# define FALSE 0

# ifndef START_COLOR
#  define START_COLOR 0x9d00ffff
# endif

# ifndef END_COLOR
#  define END_COLOR 0x40F2FFFF
# endif

# ifndef ZOOM_FACTOR
#  define ZOOM_FACTOR 0.05
# endif

# ifndef TRANSLATION_FACTOR
#  define TRANSLATION_FACTOR 3
# endif

# ifndef ROTATION_FACTOR
#  define ROTATION_FACTOR 0.1
# endif

/**
 * @brief A structure to hold type of projection
 * @param ISOMETRIC Isometric projection
 * @param PARALLEL Parallel/Ortographic projection
*/
typedef enum e_projection_type
{
	ISOMETRIC,
	PARALLEL
}	t_projection_type;

/**
 * @brief A structure to hold a 3D point
*/
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

/**
 * @brief A structure to hold a 2D point in projected coordinates
 * @param z_val The z value of the point
*/
typedef struct s_point_iso
{
	int	x;
	int	y;
	int	z_val;
}	t_point_pr;

/**
 * @brief A structure to hold the values of the isometric points, 
 * this is mostly for norminette, for calculating the isometric points
*/
typedef struct s_pt_iso_vals
{
	int	x;
	int	y;
	int	rotated_x;
	int	rotated_y;
}	t_pt_iso_vals;

/**
 * @brief A structure to hold the map
*/
typedef struct s_map
{
	int		min_z;
	int		max_z;
	int		window_width;
	int		window_height;
	int		width_x_axis;
	int		height_y_axis;
	t_point	**matrix;
}	t_map;

/**
 * @brief A structure to hold the line parameters, for Bresenham's line algorithm
*/
typedef struct s_line_params
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	t_point_pr	*p1;
	t_point_pr	*p2;
}	t_line_params;

/**
 * @brief A structure to hold the rgba values in bytes for a color
*/
typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

/**
 * @brief A structure to hold the transformation values
 * zoom, rotation, translation and type of projection
*/
typedef struct s_transform
{
	int					translation_x;
	int					translation_y;
	float				zoom;
	float				rotation;
	t_projection_type	projection;
}	t_transform;

/**
 * @brief A structure to hold the FdF application, 
 * easier to pass around and clean up
*/
typedef struct s_app
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_transform	*transform;
}	t_app;

/**
 * @brief Counts the number of new lines in the file
 * @param filename The filename
*/
int		new_line_count(char *filename);

/**
 * @brief Creates a map structure and fills it with the values from the file
 * @param filename The filename
*/
t_map	*parse_map(char *filename);

/**
 * @brief Checks if the filename is valid
 * @param filename The filename
*/
int		is_filename_valid(char *filename);

/**
 * @brief Draws the isometric projection of the map
 * @param app The application structure
*/
void	draw_pr_map(t_app *app);

/**
 * @brief Draws a line between two isometric points, Bresenham's line algorithm
 * with error correction
 * @param img The image
 * @param p1 The first point
 * @param p2 The second point
 * @param color The color
*/
void	draw_line(t_map *map, mlx_image_t *img, t_point_pr p1, t_point_pr p2);

/**
 * @brief Adds an offset to the isometric points - centering the drawing 
 * on the screen (mainly for first time drawing)
 * @param p1 The first point
 * @param p2 The second point
*/
void	apply_offset(t_point_pr *p1, t_point_pr *p2, t_map *map);

/**
 * @brief Calculates the color of the line using the z values as gradient,
 * interpolating between the start and end colors, floating point percentage 
 * could be out of bounds [0, 1], so we need to check it and round it 
 * @param map The map
 * @param line The line parameters
*/
int		calc_color(t_map *map, t_line_params *line);

/**
 * @brief Frees every malloc in the app structure (map, transform, img, mlx)
 * basically everything
 * @param app The application structure
*/
void	clean_app(t_app *app);

/**
 * @brief Parses the map and initializes the transform structure
 * @param app The application structure
 * @param filename The filename, needed for matrix in the map structure
*/
int		update_app(t_app *app, char *filename);

/**
 * @brief Zoom in the map by a constant factor,
 * works for isometric and parallel projection 
*/
void	zoom_in(t_app *app);

/**
 * @brief Zoom out the map by a constant factor,
 * works for isometric and parallel projection 
*/
void	zoom_out(t_app *app);

/**
 * @brief Translate the map to the left by a constant factor,
 * works for isometric and parallel projection 
*/
void	translate_x_left(t_app *app);

/**
 * @brief Translate the map to the right by a constant factor,
 * works for isometric and parallel projection 
*/
void	translate_x_right(t_app *app);

/**
 * @brief Translate the map up by a constant factor,
 * works for isometric and parallel projection 
*/
void	translate_y_up(t_app *app);

/**
 * @brief Translate the map down by a constant factor,
 * works for isometric and parallel projection 
*/
void	translate_y_down(t_app *app);

/**
 * @brief Rotate the map to the left by a constant factor,
 * works for isometric projection 
*/
void	rotate_2d_left(t_app *app);

/**
 * @brief Rotate the map to the right by a constant factor,
 * works for isometric projection 
*/
void	rotate_2d_right(t_app *app);

/**
 * @brief Change the projection of the map, between isometric and parallel
 * @param app The application structure
 * @param projection The projection type
*/
void	change_projection(t_app *app, t_projection_type projection);

/**
 * @brief Projects point to isometric or parallel projection, based on 
 * the transform structure
*/
t_point_pr	project_pt(t_point *pt, t_transform *tr);

#endif