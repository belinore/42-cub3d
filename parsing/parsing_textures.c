#include "../includes/cub3d.h"

// This function takes a texture line like "NO ./wall.png" and gets the path "./wall.png"
// It ignores spaces and stops at new line or space.
// Returns the path as a new string.
static char	*extract_path(char *line)
{
	char	*path;
	int		i;
	int		j;
	int		start;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	path = malloc(i - start + 1);
	if (!path)
		return (NULL);
	j = 0;
	while (start < i)
		path[j++] = line[start++];
	path[j] = '\0';
	return (path);
}

// This function sets the path string to correct texture storage.
// If path already set, returns -1 (duplicate).
static int	set_texture_path(char **dest, char *path)
{
	if (*dest)
		return (-1);
	*dest = ft_strdup(path);
	return (0);
}

// This function checks which texture line it is (NO, SO, WE, EA)
// and assigns path to the correct game texture.
static int	assign_texture(t_game *game, char *line, char *path)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture_path(&game->tex.north_path, path));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture_path(&game->tex.south_path, path));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture_path(&game->tex.west_path, path));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture_path(&game->tex.east_path, path));
	return (0);
}

// This function parses a texture line from the .cub file
// Steps:
// 1. Extract the path using extract_path()
// 2. It makes sure path of textures ends with ".xpm".
// 3. Assign it to correct texture using assign_texture()
// 4. Free temporary path string
// 5. If duplicate texture found, free all textures and show error
int	parse_texture_line(t_game *game, char *line)
{
	char	*path;
	int		result;
	size_t	len;

	path = extract_path(line);
	if (!path)
		return (ft_error("Error: Memory allocation failed for texture path"));
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		destroy_textures(game);
		free(path);
		return (ft_error("Error: Texture must be a .xpm image file"));
	}
	result = assign_texture(game, line, path);
	free(path);
	if (result != 0)
	{
		destroy_textures(game);
		return (ft_error("Error: Duplicate texture definition"));
	}
	return (0);
}
