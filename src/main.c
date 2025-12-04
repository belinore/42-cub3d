#include "../includes/cub3d.h"

static void	print_map(t_game *game)
{
	int	y;

	printf("Map Size width=%d, height=%d\n", game->map.width, game->map.height);
	y = 0;
	while (y < game->map.height)
	{
		printf("%s\n", game->map.grid[y]);
		y++;
	}
}

static void	print_player(t_game *game)
{
	printf("Player x=%f, y=%f\n", game->player.position_x,
		game->player.position_y);
	printf("Direction x=%f, y=%f\n", game->player.direction_x,
		game->player.direction_y);
	printf("Camera x=%f, y=%f\n", game->player.camera_x, game->player.camera_y);
}

static void	print_textures(t_game *game)
{
	printf("Textures:\n");
	printf("NO %s\n", game->tex.north_path);
	printf("SO %s\n", game->tex.south_path);
	printf("WE %s\n", game->tex.west_path);
	printf("EA %s\n", game->tex.east_path);
}

static void	print_colors(t_game *game)
{
	printf("Colors:\n");
	printf("  Floor: %d,%d,%d\n", game->floor_color.red,
		game->floor_color.green, game->floor_color.blue);
	printf("  Ceiling: %d,%d,%d\n", game->ceiling_color.red,
		game->ceiling_color.green, game->ceiling_color.blue);
}

// This function prepares the game structure before using it.
// It sets everything to 0 so no garbage value stays inside.
// It also sets default colors for floor and sky.

void	initialize_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = (t_color){50, 50, 50};
	game->ceiling_color = (t_color){135, 206, 235};
}

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		return (ft_error("map.cub file is missing"), 1);
	}
	initialize_game(&game);
	if (start_parsing(&game, argv) != 0)
		return (1);
	//debug output – remove before evaluation
	printf("\n Parsing Result  \n");
	print_textures(&game);
	print_colors(&game);
	print_player(&game);
	print_map(&game);
	destroy_textures(&game);
	free_map(&game);
	return (0);
}
