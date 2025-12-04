#include "../includes/cub3d.h"

// This function checks if the line is a texture line.
// Valid texture lines start with:
// "NO " (north wall image)
// "SO " (south wall image)
// "WE " (west wall image)
// "EA " (east wall image)
// If line matches, return 1
// If not, return 0
static int	is_texture_line(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

// This function checks if the line is a color line.
// Valid color lines start with:
// 'F' → floor color
// 'C' → sky/ceiling color
// If yes, return 1
// If not, return 0
static int	is_color_line(char *line)
{
	if (!line || ft_strlen(line) < 2)
		return (0);
	if (line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

// This function checks if the line belongs to the map layout.
// Map lines can only have:
// '0' (empty space), '1' (wall), space ' ',
// 'N','S','E','W' (player direction), '\n'
// If ANY other letter found → not map line  return 0
// If all letters allowed → map line return 1
static int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// This function checks every line type and sends it to the right handler:
// - Texture handler if line is texture and map not started
// - Color handler if line is color and map not started
// - Map handler if line is part of map
// If line doesn’t match anything, show error and stop safely.
int	parse_single_line(t_game *game, char *line, t_counter *counter)
{
	if (is_texture_line(line) && !counter->map_started)
		return (handle_texture_line(game, line, counter));
	else if (is_color_line(line) && !counter->map_started)
		return (handle_color_line(game, line, counter));
	else if (is_map_line(line))
		return (handle_map_line(game, line, counter));
	else
	{
		destroy_textures(game);
		return (ft_error("Error: Unknown line format"));
	}
	return (0);
}