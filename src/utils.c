#include "fdf.h"

int	new_line_count(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int	is_filename_valid(char *filename)
{
	size_t	len_filename;

	len_filename = ft_strlen(filename);
	if (len_filename < 5)
		return (FALSE);
	len_filename -= 4;
	if (ft_strncmp(filename + len_filename, ".fdf", 4) != 0)
		return (FALSE);
	return (TRUE);
}
