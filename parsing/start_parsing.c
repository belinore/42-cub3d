#include "cub3d.h"

// This function checks if file reading (parsing) is finished properly.
// It makes sure file had:
// 4 textures (NO, SO, WE, EA) and 2 colors (F, C) and 1 map.
// If anything is missing, it frees memory and shows error.
int	validate_parsing_completion(t_game *game, t_counter *counter)
{
	if (counter->texture_count != 4)
	{
		destroy_textures(game);
		return (ft_error("Error: Missing texture need NO,SO,WE,EA"));
	}
	if (counter->color_count != 2)
	{
		destroy_textures(game);
		return (ft_error("Error: Missing color need F and C"));
	}
	if (!counter->map_started)
	{
		destroy_textures(game);
		return (ft_error("Error: No map found in file"));
	}
	return (0);
}
// This function checks if the map rules are correct.
// It makes sure:
// 1. Map has only allowed letters (no other symbols)
// 2. Map has one player starting point
// 3. Map is closed properly (surrounded by walls)
// If any check fails, it stops and returns -1 (means map is bad)

// static int validate_map_shape(t_game *game)
// {
//     int x;
//     int y;

//     x = 0;
//     y = 0;
//     // Top and bottom borders
//     while( x < game->map.width)
//     {
//         if (game->map.grid[0][x] != '1')
//             return (ft_error("Error: Top border must be closed"));
//         if (game->map.grid[game->map.height-1][x] != '1')
//             return (ft_error("Error: Bottom border must be closed"));
//         destroy_textures(game);
//         x++;
//     }
// // Left and right borders
//     while (y < game->map.height)
//     {
//         if (game->map.grid[y][0] != '1')
//             return (ft_error("Error: Left border must be closed"));
//         if (game->map.grid[y][game->map.width-1] != '1')
//             return (ft_error("Error: Right border must be closed"));
//         destroy_textures(game);
//         y++;
//     }
//     return (0);
// }

int	validate_map(t_game *game)
{
	if (check_valid_chars(game) != 0)
		return (-1);
	if (validate_and_store_player(game) != 0)
		return (-1);
	if (check_map_closed(game) != 0)
		return (-1);
	return (0);
}

// This function reads the .cub file from computer and stores data in game.
// Steps:
// 1. Open the file from the given path (location)
// 2. If file not opens, show error to user
// 3. Read file line by line and process map + colors + textures
// 4. Free extra memory used by file reader
// 5. Close file for safety
// 6. Check if all important data was found (parsing complete)
// If any step fails, stop safely and return -1
int	load_cub_file(t_game *game, const char *path)
{
	t_counter	count;
	int			fd;

	count = (t_counter){0};
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Error: cannot open file"));
	if (read_cub_lines(game, fd, &count) != 0)
		return (-1);
	gnl_free(NULL);
	close(fd);
	if (validate_parsing_completion(game, &count) != 0)
		return (-1);
	return (0);
}

// This function checks if the map file name is correct.
// It makes sure the user gave a file path and file ends with ".cub".
// If the file is wrong, it prints error message.
int	is_valid_cub_file(char **argv)
{
	char	*file;

	file = argv[1];
	if (!file || ft_strlen(file) < 5)
		return (ft_error("Error: Invalid file path"));
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		return (ft_error("Error: File must have .cub extension"));
	if (ft_strnstr(file, ".cub", ft_strlen(file) - 4))
		return (ft_error("Error: Invalid file extension (double .cub detected)"));
	return (0);
}

// This function starts reading and checking the .cub map file.
// Step 1: Check file name is valid (.cub extension)
// Step 2: Read the file and load map
// Step 3: Check map rules are correct (walls, path, etc)
// If any step fails, free memory and stop program safely.
int	start_parsing(t_game *game, char **argv)
{
	if (is_valid_cub_file(argv) != 0)
		return (-1);
	if (load_cub_file(game, argv[1]) != 0)
	{
		free_map(game);
		return (-1);
	}
	if (validate_map(game) != 0)
	{
		free_map(game);
		return (-1);
	}
	return (0);
}
