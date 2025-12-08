/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:58:56 by belinore          #+#    #+#             */
/*   Updated: 2025/12/08 18:06:21 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_minimap(t_game *g, t_point p0, t_point p1, int color)
{
	t_point		d;
	int			steps;
	t_pointf	step;
	t_pointf	p;
	int			i;

	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	steps = max(iabs(d.x), iabs(d.y));
	if (steps == 0)
		return ;
	step.x = (double)d.x / steps;
	step.y = (double)d.y / steps;
	p.x = (double)p0.x;
	p.y = (double)p0.y;
	i = 0;
	while (i++ <= steps)
	{
		if ((round)(p.x) < 0 || round(p.x) >= g->minimap.width_pix
			|| round(p.y) < 0 || round(p.y) >= g->minimap.height_pix)
			return ;
		put_pixel(&g->img, round(p.x), round(p.y), color);
		p.x += step.x;
		p.y += step.y;
	}
}
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
		wall_hit_pixel.x = (int)(ray->wall.hit_pos_x * g->minimap.tile_size
			- g->minimap.camera.x);
		wall_hit_pixel.y = (int)(ray->wall.hit_pos_y * g->minimap.tile_size
			- g->minimap.camera.y);
		draw_ray_minimap(g, g->minimap.player_pixel, wall_hit_pixel, GREEN);
		wall_map_pixel.x = (int)(ray->wall.map_tile_x * g->minimap.tile_size
			- g->minimap.camera.x);
		wall_map_pixel.y = (int)(ray->wall.map_tile_y * g->minimap.tile_size
			- g->minimap.camera.y);
		draw_scaled_texture_tile(g, ray->wall.texture, &wall_map_pixel);
		i++;
	}
}

void	draw_player(t_game *g)
{
	t_point	circle_center;
	t_point	line_end;
	int		radius;
	int		line_len;

	circle_center.x = g->minimap.player_pixel.x;
	circle_center.y = g->minimap.player_pixel.y;
	if (circle_center.x < 0 || circle_center.x >= WIDTH
		|| circle_center.y < 0 || circle_center.y >= HEIGHT)
		return ;
	radius = g->minimap.tile_size / 4;
	draw_circle(&g->img, circle_center, radius, YELLOW);
	if (DEBUG_MODE)
		raycasting_minimap(g);
	line_len = g->minimap.tile_size / 3;
	line_end.x = circle_center.x + g->player.dir_x * line_len;
	line_end.y = circle_center.y + g->player.dir_y * line_len;
	draw_line(&g->img, circle_center, line_end, RED);
}

void	draw_minimap_tile(t_game *g, t_point *pixel, int i, int j)
{
	if (i < 0 || j < 0 || !g->map.grid[i])
		return ;
	else if (!g->map.grid[i][j])
		draw_tile(g, *pixel, DARK_GREY);
	else if (g->map.grid[i][j] == '1')
		draw_tile(g, *pixel, BLACK);
	else if (g->map.grid[i][j] == ' ')
		draw_tile(g, *pixel, DARK_GREY);
	else
		draw_tile(g, *pixel, WHITE);
	pixel->x += g->minimap.tile_size;
}

void	draw_full_map(t_game *g)
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
		pixel.y += g->minimap.tile_size;
		if (pixel.y >= HEIGHT)
			break ;
		i++;
	}
}

static void	calc_offsets(t_game *g, t_point *tile_offset,
	t_point *pixel_offset)
{
	tile_offset->x = (int)(g->minimap.camera.x / g->minimap.tile_size);
	tile_offset->y = (int)(g->minimap.camera.y / g->minimap.tile_size);
	pixel_offset->x = (int)(g->minimap.camera.x) % g->minimap.tile_size;
	pixel_offset->y = (int)(g->minimap.camera.y) % g->minimap.tile_size;
}

void	draw_minimap_view(t_game *g)
{
	int			i;
	int			j;
	t_point		pixel;
	t_point		tile_offset;
	t_point		pixel_offset;

	calc_offsets(g, &tile_offset, &pixel_offset);
	pixel.x = -pixel_offset.x;
	pixel.y = -pixel_offset.y;
	i = tile_offset.y;
	while (i < tile_offset.y + g->minimap.height_map + 1)
	{
		j = tile_offset.x;
		pixel.x = -pixel_offset.x;
		while (j < tile_offset.x + g->minimap.width_map + 1)
		{
			draw_minimap_tile(g, &pixel, i, j);
			j++;
		}
		if (i > 0 && !g->map.grid[i])
			break ;
		pixel.y += g->minimap.tile_size;
		i++;
	}
}

//calculates which part of the map to draw based on player position.
//camera is the top-left pixel of the minimap, with the player in the centre.
//offset_tile is which tile to start drawing from, and offset_pixel enables 
//drawing of partial tiles by shifting start position off the screen.
void	draw_minimap(t_game *g)
{
	if (g->minimap.width_map == g->map.width
		&& g->minimap.height_map == g->map.height)
	{
		draw_full_map(g);
		g->minimap.player_pixel.x = g->player.pixel.x;
		g->minimap.player_pixel.y = g->player.pixel.y;
	}
	else
	{
		g->minimap.camera.x = g->player.pixel.x - (g->minimap.width_pix / 2);
		g->minimap.camera.y = g->player.pixel.y - (g->minimap.height_pix / 2);
		if (g->minimap.camera.x < 0)
			g->minimap.camera.x = 0;
		if (g->minimap.camera.y < 0)
			g->minimap.camera.y = 0;
		draw_minimap_view(g);
		g->minimap.player_pixel.x = g->player.pixel.x - g->minimap.camera.x;
		g->minimap.player_pixel.y = g->player.pixel.y - g->minimap.camera.y;
	}
	draw_player(g);
}
