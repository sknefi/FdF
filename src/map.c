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
		return (-1);
	curr_x_index = 0;
	while (split_line[curr_x_index])
	{
		map->matrix[curr_y_index][curr_x_index].x = curr_x_index;
		map->matrix[curr_y_index][curr_x_index].y = curr_y_index;
		map->matrix[curr_y_index][curr_x_index].z = ft_atoi(
				split_line[curr_x_index]);
		curr_x_index++;
	}
	return (1);
}

/**
 * @brief Fills the matrix with the values from the file.
 * @param map The map structure
 * @param numbers_count The numbers count in the line
 * @param curr_y_index The current y index - the line index
 * @param filename The filename
 * @return 1 if successful, 0 if end of file / empty, -1 if error
*/
static int	fill_matrix_loop(int fd,
	int *numbers_count, int *curr_y_index, t_map *map)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	split_line = ft_split(line, ' ');
	free(line);
	if (!split_line)
		return (-1);
	(*numbers_count) = ft_split_len(split_line);
	if (map->width_x_axis == 0)
		map->width_x_axis = *numbers_count;
	else if (map->width_x_axis != (*numbers_count))
		return (free_split(split_line), -1);
	if (insert_points(map, split_line, *curr_y_index) < 0)
		return (free_split(split_line), -1);
	(*curr_y_index)++;
	free_split(split_line);
	return (1);
}

int	fill_matrix(t_map *map, char *filename)
{
	int		fd;
	int		res;
	int		numbers_count;
	int		curr_y_index;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	curr_y_index = 0;
	numbers_count = 0;
	while (TRUE)
	{
		res = fill_matrix_loop(fd, &numbers_count, &curr_y_index, map);
		if (res == 0)
			break ;
		if (res == -1)
			return (close(fd), -1);
	}
	close(fd);
	return (1);
}

void	find_min_max_in_matrix(t_map *map)
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

void	draw_pr_map(t_app *app)
{
	int			i;
	int			j;
	t_pt_pr		p1;

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
