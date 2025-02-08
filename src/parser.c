#include "fdf.h"

static int	insert_points(t_map *map, char **split_line, int curr_y_index)
{
	int		curr_x_index;

	map->matrix[curr_y_index] = (t_point *)malloc(sizeof(t_point) * map->width_x_axis);
	if (map->matrix[curr_y_index] == NULL)
		return (-1); // error
	curr_x_index = 0;
	while (split_line[curr_x_index])
	{
		map->matrix[curr_y_index][curr_x_index].x = curr_x_index;
		map->matrix[curr_y_index][curr_x_index].y = curr_y_index;
		map->matrix[curr_y_index][curr_x_index].z = ft_atoi(split_line[curr_x_index]);
		map->matrix[curr_y_index][curr_x_index].color = 0xFFFFFF;
		curr_x_index++;
	}
	free_split(split_line);
	return (1);
}

static int	fill_values(t_map *map, char *filename)
{
	int		fd;
	int		numbers_count;
	int		curr_y_index;
	char	*line;
	char	**split_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1); // error
	curr_y_index = 0;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			return (close(fd), -1); // error
		numbers_count = ft_split_len(split_line);
		if (map->width_x_axis == 0) // tu to teoreticky moze failnut
			map->width_x_axis = numbers_count;
		else if (map->width_x_axis != numbers_count)
			return (free_split(split_line), close(fd), -1); // error
		if (insert_points(map, split_line, curr_y_index) < 0)
			return (close(fd), -1); // error
		curr_y_index++;
	}
	close(fd);
	return (1);
}

t_map	*parse_map(char *filename)
{
	int		nl_count;
	t_map	*map;

	nl_count = new_line_count(filename);
	if (nl_count == -1 || nl_count == 0)
		return (NULL); // error
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL); // error
	map->width_x_axis = 0;
	map->height_y_axis = nl_count;
	map->matrix = (t_point **)malloc(sizeof(t_point *) * nl_count);
	if (!map->matrix)
		return (free(map), NULL); // error
	if (fill_values(map, filename) < 0)
		return (free(map->matrix), free(map), NULL); // error
	return (map);
}
