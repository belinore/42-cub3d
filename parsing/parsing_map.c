#include "../includes/cub3d.h"

// This function calculates the length of a line after removing the last '\n' (new line).
// It helps to know the real map line size without the new line symbol.
// If line is NULL, return 0 .
static int	get_trimed_len(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

// This function copies the map line into new memory (new string).
// It copies only valid letters up to "len" size and adds '\0' at end.
// If memory not given, return NULL
static char	*dup_map_line(char *line, int len)
{
	char	*map_line;
	int		i;

	map_line = ft_calloc(len + 1, sizeof(char));
	if (!map_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map_line[i] = line[i];
		i++;
	}
	return (map_line);
}

// This function makes the map grid (2D array) bigger when new line needs to be added.
// It copies old lines into new bigger box safely.
// After copying, it removes (free) the old box to avoid memory waste.
// If memory not given, show error and return NULL
static char	**resize_map_grid(char **old_grid, int needed)
{
	char	**new_grid;
	int		i;

	new_grid = ft_calloc(sizeof(char *), needed);
	if (!new_grid)
	{
		ft_error("Error: Memory allocation failed for map grid");
		return (NULL);
	}
	i = 0;
	if (old_grid)
	{
		while (old_grid[i])
		{
			new_grid[i] = old_grid[i];
			i++;
		}
		free(old_grid);
	}
	return (new_grid);
}

// This function adds one new map line into the game map grid.
// Steps:
// 1. Remove new line symbol and get real length
// 2. Duplicate the map line safely into new memory
// 3. Make map grid bigger to store this new line
// 4. Add the line into grid + update map height and width
// If any step fails, free memory and stop safely
int	append_map_line(t_game *game, char *line, int line_index)
{
	int		len;
	char	*map_line;
	char	**new_grid;

	if (!line)
		return (ft_error("Error: NULL line passed to append_map_line"));
	len = get_trimed_len(line);
	map_line = dup_map_line(line, len);
	if (!map_line)
		return (ft_error("Error: Memory allocation failed for map line"));
	new_grid = resize_map_grid(game->map.grid, line_index + 2);
	if (!new_grid)
	{
		free(map_line);
		ft_error("Error: Memory allocation failed for new grid");
		return (-1);
	}
	game->map.grid = new_grid;
	game->map.grid[line_index] = map_line;
	game->map.grid[line_index + 1] = NULL;
	game->map.height = line_index + 1;
	if (len > game->map.width)
		game->map.width = len;
	return (0);
}
