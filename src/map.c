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
	if (fd < 0)
		return (-1);
	curr_y_index = 0;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			return (close(fd), -1);
		numbers_count = ft_split_len(split_line);
		if (map->width_x_axis == 0)
			map->width_x_axis = numbers_count;
		else if (map->width_x_axis != numbers_count)
			return (free_split(split_line), close(fd), -1);
		if (insert_points(map, split_line, curr_y_index) < 0)
			return (close(fd), -1);
		curr_y_index++;
	}
	close(fd);
	return (1);
}

/**
 * @brief Finds the minimum and maximum values in the matrix (on the z axis)
 * @param map The map structure
*/
static void	find_min_max_in_matrix(t_map *map)
{
	int		i;
	int		j;

	map->min_z = map->matrix[0][0].z;
	map->max_z = map->matrix[0][0].z;
	i = 0;
	while (i < map->height_y_axis)
	{
		j = 0;
		while (j < map->width_x_axis)
		{
			if (map->matrix[i][j].z < map->min_z)
				map->min_z = map->matrix[i][j].z;
			if (map->matrix[i][j].z > map->max_z)
				map->max_z = map->matrix[i][j].z;
			j++;
		}
		i++;
	}
}

t_map	*parse_map(char *filename)
{
	int			nl_count;
	t_map		*map;

	nl_count = new_line_count(filename);
	if (nl_count == -1 || nl_count == 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width_x_axis = 0;
	map->height_y_axis = nl_count;
	map->window_width = WINDOW_WIDTH;
	map->window_height = WINDOW_HEIGHT;
	map->matrix = (t_point **)malloc(sizeof(t_point *) * nl_count);
	if (!map->matrix)
		return (free(map), NULL);
	if (fill_matrix(map, filename) < 0)
		return (free(map->matrix), free(map), NULL);
	find_min_max_in_matrix(map);
	return (map);
}

void	draw_iso_map(t_app *app)
{
	int			i;
	int			j;
	t_point_pr	p1;

	i = 0;
	while (i < app->map->height_y_axis)
	{
		j = 0;
		while (j < app->map->width_x_axis)
		{
			p1 = project_pt(&app->map->matrix[i][j], app->transform);
			if (j + 1 < app->map->width_x_axis)
				draw_line(app->map, app->img, p1,
					project_pt(&app->map->matrix[i][j + 1], app->transform));
			if (i + 1 < app->map->height_y_axis)
				draw_line(app->map, app->img, p1,
					project_pt(&app->map->matrix[i + 1][j], app->transform));
			j++;
		}
		i++;
	}
}
