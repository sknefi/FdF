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

int		new_line_count(char *filename);
t_map	*parse_map(char *filename);

#endif