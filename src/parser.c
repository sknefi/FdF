#include "fdf.h"

/**
 * @brief Counts the number of new lines in the file.
 * @param map The map structure
 * @param split_line The split line
 * @param curr_y_index The current y index
*/
static int	insert_points(t_map *map, char **split_line, int curr_y_index)
{
	int		curr_x_index;

	map->matrix[curr_y_index] = (t_point *)
		malloc(sizeof(t_point) * map->width_x_axis);
	if (map->matrix[curr_y_index] == NULL)
		return (-1); // error
	curr_x_index = 0;
	while (split_line[curr_x_index])
	{
		map->matrix[curr_y_index][curr_x_index].x = curr_x_index;
		map->matrix[curr_y_index][curr_x_index].y = curr_y_index;
		map->matrix[curr_y_index][curr_x_index].z = ft_atoi(
				split_line[curr_x_index]);
		curr_x_index++;
	}
	free_split(split_line);
	return (1);
}

/**
 * @brief Fills the matrix with the values from the file.
 * @param map The map structure
 * @param filename The filename
*/
static int	fill_matrix(t_map *map, char *filename)
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
		return (NULL); // error or empty file
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL); // error
	map->width_x_axis = 0;
	map->height_y_axis = nl_count;
	map->window_width = WIDTH;
	map->window_height = HEIGHT;
	map->matrix = (t_point **)malloc(sizeof(t_point *) * nl_count);
	if (!map->matrix)
		return (free(map), NULL); // error
	if (fill_matrix(map, filename) < 0)
		return (free(map->matrix), free(map), NULL); // error
	return (map);
}

void	print_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("---------\n");
	ft_printf("Map:\n");
	ft_printf("window_width: %d\n", map->window_width);
	ft_printf("window_height: %d\n", map->window_height);
	ft_printf("width_x_axis: %d\n", map->width_x_axis);
	ft_printf("height_y_axis: %d\n", map->height_y_axis);
	ft_printf("---------\n");
	while (i < map->height_y_axis)
	{
		j = 0;
		while (j < map->width_x_axis)
		{
			ft_printf("%d ", map->matrix[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
