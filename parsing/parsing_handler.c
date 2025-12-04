#include "../includes/cub3d.h"

// This function reads texture path lines like NO, SO, WE, EA.
// It checks if user already gave 4 textures. More than 4 is not allowed.
// If line is correct, it saves texture path and increases texture count.
int	handle_texture_line(t_game *game, char *line, t_counter *counter)
{
	if (counter->texture_count == 4)
	{
		destroy_textures(game);
		return (ft_error("Error: Only 4 textures paths are allowd"));
	}
	if (parse_texture_line(game, line) != 0)
		return (-1);
	counter->texture_count++;
	return (0);
}

void	free_rgb_textures(t_game *game, char *rgb_str)
{
	free(rgb_str);
	destroy_textures(game);
}

// This function reads color lines (F for floor, C for ceiling/sky).
// It checks if 2 colors are already saved. More than 2 is not allowed.
// If line is correct, it saves color and increases color count.
int	handle_color_line(t_game *game, char *line, t_counter *counter)
{
	if (counter->color_count == 2)
	{
		destroy_textures(game);
		return (ft_error("Error: Only 2 color are allowed"));
	}
	if (parse_color_line(game, line) != 0)
		return (-1);
	counter->color_count++;
	return (0);
}

// This function reads map design line by line.
// When first map line comes, it marks map as started.
// It adds every line to map storage. If any line add fails, stop safely.
int	handle_map_line(t_game *game, char *line, t_counter *counter)
{
	if (!counter->map_started)
		counter->map_started = 1;
	if (append_map_line(game, line, counter->map_line_index) != 0)
	{
		destroy_textures(game);
		return (1);
	}
	counter->map_line_index++;
	return (0);
}
