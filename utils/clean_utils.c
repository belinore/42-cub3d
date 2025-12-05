#include "cub3d.h"

void	destroy_textures(t_game *game)
{
	if (game->tex_path.north_path)
		free(game->tex_path.north_path);
	if (game->tex_path.south_path)
		free(game->tex_path.south_path);
	if (game->tex_path.east_path)
		free(game->tex_path.east_path);
	if (game->tex_path.west_path)
		free(game->tex_path.west_path);
	if (game->textures.north.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.north.img_ptr);
	if (game->textures.south.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.south.img_ptr);
	if (game->textures.east.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.east.img_ptr);
	if (game->textures.south.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.west.img_ptr);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.width = 0;
}

void	*gnl_free(void *str)
{
	if (!str)
		get_next_line(-1);
	else
		free(str);
	return (NULL);
}

int	ft_error(char *message)
{
	if (message)
	{
		ft_putendl_fd(message, 2);
	}
	return (-1);
}
