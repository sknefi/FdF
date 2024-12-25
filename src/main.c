#include "../libft_divinus/libft.h"

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);  // Open the file in read-only mode
	if (fd == -1)  // Check if the file opened successfully
	{
		perror("Error opening file");
		return (1);
	}

	line = NULL;
	while ((line = get_next_line(fd)) != NULL)  // Read each line until EOF
	{
		ft_printf("%s\n", line);  // Print the line
		free(line);  // Free the memory allocated for the line
	}
	close(fd);  // Close the file descriptor after usage
	return (0);
}
