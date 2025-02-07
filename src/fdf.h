#ifndef FDF_H

# include <stdio.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <fcntl.h>

# define WIDTH 512
# define HEIGHT 512
# define TITLE "FdF"
# define TRUE 1
# define FALSE 0

typedef struct point_s
{
	int	x;
	int	y;
	int	z;
	int	color;
} point_t;

typedef struct map_s
{
	int		width_x_axis;
	int		height_y_axis;
	point_t	**map;
} map_t;


#endif