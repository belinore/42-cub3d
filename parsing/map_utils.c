#include "cub3d.h"

// This function checks if a map edge is open (not closed by wall).
// It takes a direction code like "x-1", "x+1", "y-1", "y+1"
// If code is wrong and neighbor not found → free all texture memory and show error.
static int	map_not_close(t_game *game, char n, char *c)
{
	if (!n)
	{
		destroy_textures(game);
		if (ft_strncmp(c, "x-1", 3) == 0)
			return (ft_error("Error: Map is not closed on the left border"));
		if (ft_strncmp(c, "x+1", 3) == 0)
			return (ft_error("Error: Map is not closed on the Right border"));
		if (ft_strncmp(c, "y+1", 3) == 0)
			return (ft_error("Error: Map is not closed on the Bottom border"));
		if (ft_strncmp(c, "y-1", 3) == 0)
			return (ft_error("Error: Map is not closed on the Top border"));
	}
	return (0);
}

// This function checks if the neighbor cell exists inside the map.
// It makes sure x and y are inside safe map range.
// It checks grid row is present and x is not bigger than the row length.
// Return 1 if neighbor exists.
// Return 0 if outside map or not found.
static int	is_valid_neighbor(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0)
		return (0);
	if (!game->map.grid[y])
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y]))
		return (0);
	return (1);
}

// This function checks 4 directions around one cell:
// left, right, top, bottom.
// It calls is_valid_neighbor() and map_not_close()
// If any direction is open → return 1 (means map open somewhere)
// If all safe → return 0 ✅ (means map closed around this cell)
static int	check_neighbors(t_game *game, int x, int y)
{
	char	n;

	n = is_valid_neighbor(game, x - 1, y);
	if (map_not_close(game, n, "x-1") != 0)
		return (1);
	n = is_valid_neighbor(game, x + 1, y);
	if (map_not_close(game, n, "x+1") != 0)
		return (1);
	n = is_valid_neighbor(game, x, y - 1);
	if (map_not_close(game, n, "y-1") != 0)
		return (1);
	n = is_valid_neighbor(game, x, y + 1);
	if (map_not_close(game, n, "y+1") != 0)
		return (1);
	return (0);
}

// This function scans the whole map and checks all letters are allowed.
// Allowed letters are:
// '1' wall, '0' empty, space, N,S,E,W (player start side)
// If any other letter/symbol found → stop and show error .
// If all ok → return 0.
int	check_valid_chars(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i] && game->map.grid[i][j])
		{
			c = game->map.grid[i][j];
			if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				return (ft_error("Error: Invalid character in map"));
			j++;
		}
		i++;
	}
	return (0);
}

// This function scans the map to make sure map is fully surrounded by walls.
// It checks only important cells ('0' or player symbols).
// For each, it checks neighbors using check_neighbors().
// If any open spot on map border → give error stop.
// If full map safe → return 0 .
int	check_map_closed(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y] && game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (check_neighbors(game, x, y) != 0)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
