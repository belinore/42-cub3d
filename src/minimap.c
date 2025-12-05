/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:58:56 by belinore          #+#    #+#             */
/*   Updated: 2025/12/05 15:29:50 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//raycasting visualisaton on minimap using data from stored rays
void	raycasting_minimap(t_game *g)
{
	t_ray	*ray;
	t_point	wall_hit_pixel;
	t_point	wall_map_pixel;
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		ray = &g->rays[i];
		wall_hit_pixel.x = (int)(ray->wall.hit_pos_x * g->tile_size);
		wall_hit_pixel.y = (int)(ray->wall.hit_pos_y * g->tile_size);
		draw_line(&g->img, g->player.pixel, wall_hit_pixel, GREEN);
		wall_map_pixel.x = (int)(ray->wall.map_tile_x * g->tile_size);
		wall_map_pixel.y = (int)(ray->wall.map_tile_y * g->tile_size);
		draw_scaled_texture_tile(&g->img, ray->wall.texture,
			&wall_map_pixel, g->tile_size);
		i++;
	}
}

void	draw_player(t_game *g)
{
	t_point	line_end;
	t_point	circle_center;
	int		radius;
	int		line_len;

	if (g->player.pixel.x < 0 || g->player.pixel.x >= WIDTH
		|| g->player.pixel.y < 0 || g->player.pixel.y >= HEIGHT)
		return ;
	radius = g->tile_size / 4;
	circle_center.x = g->player.pixel.x;
	circle_center.y = g->player.pixel.y;
	draw_circle(&g->img, circle_center, radius, YELLOW);
	if (DEBUG_MODE)
		raycasting_minimap(g);
	line_len = g->tile_size / 3;
	line_end.x = g->player.pixel.x + g->player.dir_x * line_len;
	line_end.y = g->player.pixel.y + g->player.dir_y * line_len;
	draw_line(&g->img, g->player.pixel, line_end, RED);
}

void	draw_minimap_tile(t_game *g, t_point *pixel, int i, int j)
{
	if (g->map.grid[i][j] == '1')
		draw_tile(g, *pixel, BLACK);
	else if (g->map.grid[i][j] == ' ')
		draw_tile(g, *pixel, DARK_GREY);
	else
		draw_tile(g, *pixel, WHITE);
	pixel->x += g->tile_size;
	if (g->map.grid[i][j + 1] || pixel->x >= WIDTH)
		return ;
	while (j < g->map.width)
	{
		draw_tile(g, *pixel, DARK_GREY);
		pixel->x += g->tile_size;
		if (pixel->x >= WIDTH)
			return ;
		j++;
	}
}

void	draw_minimap(t_game *g)
{
	int		i;
	int		j;
	t_point	pixel;

	i = 0;
	pixel.y = 0;
	while (g->map.grid[i])
	{
		j = 0;
		pixel.x = 0;
		while (g->map.grid[i][j])
		{
			draw_minimap_tile(g, &pixel, i, j);
			if (pixel.x >= WIDTH)
				break ;
			j++;
		}
		pixel.y += g->tile_size;
		if (pixel.y >= HEIGHT)
			break ;
		i++;
	}
	draw_player(g);
}
