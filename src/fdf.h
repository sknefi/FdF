#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include "../libft_divinus/libft.h"

# define WIDTH 512
# define HEIGHT 512
# define TITLE "FdF"
# define TRUE 1
# define FALSE 0

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width_x_axis;
	int		height_y_axis;
	t_point	**matrix;
}	t_map;

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
*/
void	free_map(t_map *map);
#endif