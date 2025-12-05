#include "cub3d.h"

// This function checks if the line is empty or only new line.
// It helps to skip useless lines before map.
static int	is_empty_line(char *line)
{
	return (ft_strlen(line) == 0 || line[0] == '\n');
}

// This function checks every single line from file and sends it for parsing.
// If line is empty inside the map, it stops and shows error.
// If parsing fails, it returns -1 to stop whole process.
int	handle_line(t_game *game, char *line, t_counter *counter)
{
	if (is_empty_line(line))
	{
		if (counter->map_started)
		{
			destroy_textures(game);
			return (ft_error("Error: Found empty line inside map"));
		}
		return (1);
	}
	if (parse_single_line(game, line, counter) != 0)
	{
		return (-1);
	}
	return (0);
}

// This function reads .cub file one line at a time using line reader tool.
// It runs loop until file ends.
// It checks every line and stops safely if any error comes.
// It also frees memory and closes file at exit.
int	read_cub_lines(t_game *game, int fd, t_counter *counter)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		result = handle_line(game, line, counter);
		free(line);
		if (result == 1)
		{
			line = get_next_line(fd);
			continue ;
		}
		if (result == -1)
		{
			gnl_free(NULL);
			close(fd);
			return (-1);
		}
		line = get_next_line(fd);
	}
	return (0);
}
