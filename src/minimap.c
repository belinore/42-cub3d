/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:58:56 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 16:00:43 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//raycasting visualisaton on minimap using data from stored rays
void	raycasting_minimap(t_game *game)
{
	t_ray	*ray;
	t_point	wall_hit_pixel;
	t_point	wall_map_pixel;
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		ray = &game->rays[i];
		wall_hit_pixel.x = (int)(ray->wall.hit_pos_x * TILE_SIZE);
		wall_hit_pixel.y = (int)(ray->wall.hit_pos_y * TILE_SIZE);
		draw_line(&game->img, game->player.pixel, wall_hit_pixel, GREEN);
		wall_map_pixel.x = (int)(ray->wall.map_tile_x * TILE_SIZE);
		wall_map_pixel.y = (int)(ray->wall.map_tile_y * TILE_SIZE);
		draw_scaled_texture_tile(&game->img, ray->wall.texture,
			&wall_map_pixel, TILE_SIZE);
		i++;
	}
}

void	draw_player(t_game *game)
{
	t_point	line_end;
	t_point	circle_center;
	int		radius;
	int		line_len;

	if (game->player.pixel.x < 0 || game->player.pixel.x >= WIDTH
		|| game->player.pixel.y < 0 || game->player.pixel.y >= HEIGHT)
		return ;
	radius = TILE_SIZE / 4;
	circle_center.x = game->player.pixel.x;
	circle_center.y = game->player.pixel.y;
	draw_circle(&game->img, circle_center, radius, YELLOW);
	if (DEBUG_MODE)
		raycasting_minimap(game);
	line_len = TILE_SIZE / 3;
	line_end.x = game->player.pixel.x + game->player.dir_x * line_len;
	line_end.y = game->player.pixel.y + game->player.dir_y * line_len;
	draw_line(&game->img, game->player.pixel, line_end, RED);
}

void	draw_minimap_tile(t_game *game, t_point *pixel, int i, int j)
{
	if ((game->map[i][j] == '1' && i == 0)
		|| (game->map[i][j] == '1' && game->map[i - 1][j] == ' '))
		draw_scaled_texture_tile(&game->img, &game->textures.north,
			pixel, TILE_SIZE);
	else if ((game->map[i][j] == '1' && i == game->map_height - 1)
		|| (game->map[i][j] == '1' && game->map[i + 1][j] == ' '))
		draw_scaled_texture_tile(&game->img, &game->textures.south,
			pixel, TILE_SIZE);
	else if ((game->map[i][j] == '1' && j == 0)
		|| (game->map[i][j] == '1' && game->map[i][j - 1] == ' '))
		draw_scaled_texture_tile(&game->img, &game->textures.west,
			pixel, TILE_SIZE);
	else if ((game->map[i][j] == '1' && j == game->map_width - 1)
		|| (game->map[i][j] == '1' && game->map[i][j + 1] == ' '))
		draw_scaled_texture_tile(&game->img, &game->textures.east,
			pixel, TILE_SIZE);
	else if (game->map[i][j] == '1')
		draw_tile(game, *pixel, BLACK);
	else if (game->map[i][j] == ' ')
		draw_tile(game, *pixel, WHITE);
	else
		draw_tile(game, *pixel, LIGHT_GREY);
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		j;
	t_point	pixel;

	i = 0;
	pixel.y = 0;
	while (game->map[i])
	{
		j = 0;
		pixel.x = 0;
		while (j < game->map_width)
		{
			draw_minimap_tile(game, &pixel, i, j);
			pixel.x += TILE_SIZE;
			if (pixel.x >= WIDTH)
				break ;
			j++;
		}
		pixel.y += TILE_SIZE;
		if (pixel.y >= HEIGHT)
			break ;
		i++;
	}
	draw_player(game);
}
