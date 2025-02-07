#include "fdf.h"

map_t	*parse_map(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	
}