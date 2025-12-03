/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:53:14 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 15:53:16 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_camera(t_game *game)
{
	double	camera_plane_scale;
	int		x;

	camera_plane_scale = tan(FOV / 2);
	game->player.plane_x = -game->player.dir_y * camera_plane_scale;
	game->player.plane_y = game->player.dir_x * camera_plane_scale;
	game->dist_to_camera_plane = (WIDTH / 2) / tan(FOV / 2);
	x = 0;
	while (x < WIDTH)
	{
		game->camera_x[x] = scale_pixel(x, -1.0, 1.0, WIDTH - 1);
		x++;
	}
}

void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

void	init_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				game->player.map_x = x;
				game->player.map_y = y;
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				game->player.pixel.x = (int)(game->player.pos_x * TILE_SIZE);
				game->player.pixel.y = (int)(game->player.pos_y * TILE_SIZE);
				set_player_direction(game, game->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

//map data is temp to be replaced with parsed map from file
void	init_game(t_game *game)
{
	static char	*map_data[] = {
		"   1111111",
		"1111000001",
		"1000001101",
		"1000000001",
		"1000110001",
		"1000E00101",
		"1000000001",
		"1111111111",
		NULL
	};

	game->map = map_data;
	game->map_height = 8;
	game->map_width = 10;
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	init_textures(game);
	init_player(game);
	init_camera(game);
	init_hooks(game);
}
