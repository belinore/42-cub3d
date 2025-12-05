/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:53:14 by belinore          #+#    #+#             */
/*   Updated: 2025/12/03 19:07:45 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_camera(t_game *g)
{
	double	camera_plane_scale;
	int		x;

	camera_plane_scale = tan(g->fov / 2);
	g->player.plane_x = -g->player.dir_y * camera_plane_scale;
	g->player.plane_y = g->player.dir_x * camera_plane_scale;
	g->dist_to_camera_plane = (WIDTH / 2) / tan(g->fov / 2);
	x = 0;
	while (x < WIDTH)
	{
		g->camera_x[x] = scale_pixel(x, -1.0, 1.0, WIDTH - 1);
		x++;
	}
}

void	set_player_direction(t_game *g, char direction)
{
	if (direction == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1;
	}
	else if (direction == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
	}
	else if (direction == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
	}
	else if (direction == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
	}
}

void	init_player(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == 'N' || g->map.grid[y][x] == 'S'
				|| g->map.grid[y][x] == 'E' || g->map.grid[y][x] == 'W')
			{
				g->player.map_x = x;
				g->player.map_y = y;
				g->player.pos_x = x + 0.5;
				g->player.pos_y = y + 0.5;
				g->player.pixel.x = (int)(g->player.pos_x * g->tile_size);
				g->player.pixel.y = (int)(g->player.pos_y * g->tile_size);
				set_player_direction(g, g->map.grid[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

//map data is temp to be replaced with parsed map from file
//fov initialised to 60 degrees
void	init_game(t_game *g)
{
	// g->map.height = 8;
	// g->map.width = 10;
	// g->mouse_x = WIDTH / 2;
	// g->mouse_y = HEIGHT / 2;
	// g->fov = PI / 3;
	// g->tile_size = (int)(HEIGHT * 0.04);

	g->mouse_x = WIDTH / 2;
    g->mouse_y = HEIGHT / 2;
    g->fov = PI / 3;
    g->tile_size = (int)(HEIGHT * 0.04);

	init_textures(g);
	init_player(g);
	init_camera(g);
	init_hooks(g);
}
