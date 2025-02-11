#include "fdf.h"


/**
 * @brief Counts the number of lines in a file.
 * @param filename The name of the file.
 * @return -1 if an error occurs, otherwise the number of lines.
*/
int	new_line_count(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}