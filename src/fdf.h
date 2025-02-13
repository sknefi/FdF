#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <math.h> 
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include "../libft_divinus/libft.h"

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

# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0x00FFFF
# endif

# ifndef START_COLOR
#  define START_COLOR 0x9d00ffff
# endif

# ifndef END_COLOR
#  define END_COLOR 0x40F2FFFF
# endif

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
 * @brief A structure to hold a 2D point in isometric coordinates
*/
typedef struct s_point_iso
{
	int	x;
	int	y;
	int	z_val;
	int	color;
}	t_point_iso;

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
	t_point_iso	*p1;
	t_point_iso	*p2;
}	t_line_params;

/**
 * @brief A structure to hold the rgba values
*/
typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

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
 * @brief Prints the map
 * @param map The map structure
*/
void	print_map(t_map *map);

/**
 * @brief Frees the whole map
 * @param map The map structure
*/
void	free_map(t_map *map);

/**
 * @brief Checks if the filename is valid
 * @param filename The filename
*/
int		is_filename_valid(char *filename);

/**
 * @brief Draws the isometric projection of the map
 * @param map The map
 * @param img The image to draw on
*/
void	draw_iso_map(t_map *map, mlx_image_t *img);

/**
 * @brief Safely put a pixel on the image, 
 * checking if the coordinates are within bounds
 * @param img The image
 * @param x The x coordinate
 * @param y The y coordinate
 * @param color The color
*/
void	safe_put_pixel(mlx_image_t *img, int x, int y, int color);

/**
 * @brief Draws a line between two isometric points, Bresenham's line algorithm
 * @param img The image
 * @param p1 The first point
 * @param p2 The second point
 * @param color The color
*/
void	draw_line(t_map *map, mlx_image_t *img, t_point_iso p1, t_point_iso p2);

/**
 * @brief Adds an offset to the isometric points - centering the drawing
 * @param p1 The first point
 * @param p2 The second point
*/
void	apply_offset(t_point_iso *p1, t_point_iso *p2, t_map *map);

/**
 * @brief Calculates the color of the line using the z values as gradient,
 * interpolating between the start and end colors, floating point percentage 
 * could be out of bounds [0, 1], so we need to check it and round it
 * @param map The map
 * @param line The line parameters
*/
int	calc_color(t_map *map, t_line_params *line);

void	cleanup(t_map *map, mlx_t *mlx, mlx_image_t *img);

#endif