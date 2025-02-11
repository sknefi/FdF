#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <math.h> 
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include "../libft_divinus/libft.h"

# ifndef WIDTH
#  define WIDTH 1600
# endif

# ifndef HEIGHT
#  define HEIGHT 1600
# endif

// Offsets for centering the isometric projection
# define X_OFFSET (WIDTH / 3)
# define Y_OFFSET (HEIGHT / 5)

# define TITLE "FdF"
# define TRUE 1
# define FALSE 0

# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0xFFFFFFF
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
	int	color;
}	t_point_iso;

/**
 * @brief A structure to hold the map
*/
typedef struct s_map
{
	int		width_x_axis;
	int		height_y_axis;
	t_point	**matrix;
}	t_map;

/**
 * @brief A structure to hold the line parameters, for Bresenham's line algorithm
*/
typedef struct s_line_params
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line_params;

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
void	draw_line(mlx_image_t *img, t_point_iso p1, t_point_iso p2);

/**
 * @brief Draws a line between two isometric points, Bresenham's line algorithm
 * @param img The image
 * @param p1 The first point
 * @param p2 The second point
 * @param params The line parameters
*/
void	bresenham_line_loop(mlx_image_t *img, t_point_iso p1,
			t_point_iso p2, t_line_params params);

/**
 * @brief Adds an offset to the isometric points
 * @param p1 The first point
 * @param p2 The second point
*/
void	apply_offset(t_point_iso *p1, t_point_iso *p2);

#endif