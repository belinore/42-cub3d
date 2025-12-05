#include "cub3d.h"

// This function sets player facing East or West.
// If player direction is East → face right side.
// If West → face left side.
// It also sets camera view numbers for left-right looking angle.
static void	orientation_east_or_west(t_game *game, char c)
{
	if (c == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

// This function sets player facing North or South.
// If North → face up side.
// If South → face down side.
// It also sets camera view numbers for up-down looking angle.
static void	orientation_north_or_south(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

// This function checks one map cell for player symbol (N, S, E, W).
// If symbol found:
// 1. Increase player count.
// 2. Save player exact position in map center of that block.
// 3. Set direction and camera using orientation functions.
static void	process_cell_player(t_game *game, int i, int j, int *count)
{
	char	c;

	c = game->map.grid[i][j];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return ;
	(*count)++;
	game->player.pos_x = (double)j + 0.5;
	game->player.pos_y = (double)i + 0.5;
	if (c == 'N' || c == 'S')
		orientation_north_or_south(game, c);
	if (c == 'E' || c == 'W')
		orientation_east_or_west(game, c);
}

// This function scans the whole map to find the player start point.
// It reads map like a teacher reads notebook line by line, letter by letter.
// Rules it checks at end:
// - If no player → error stop
// - If more than 1 player → error  stop
// - If only 1 player → save data  return 0
int	validate_and_store_player(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i] && game->map.grid[i][j])
		{
			process_cell_player(game, i, j, &count);
			j++;
		}
		i++;
	}
	if (count == 0)
		return (destroy_textures(game),
			ft_error("Error: No Player Found in map"));
	if (count > 1)
		return (destroy_textures(game),
			ft_error("Error: Multiple players found in map only one allowed"));
	return (0);
}
