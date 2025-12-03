/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:40:55 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 15:41:34 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA algorithm
void	draw_line(t_img *img, t_point p0, t_point p1, int color)
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
	while (i <= steps)
	{
		put_pixel(img, round(p.x), round(p.y), color);
		p.x += step.x;
		p.y += step.y;
		i++;
	}
}

void	draw_circle(t_img *img, t_point center, int radius, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = center.x + x;
			dy = center.y + y;
			if (x * x + y * y <= radius * radius)
				put_pixel(img, dx, dy, color);
			x++;
		}
		y++;
	}
}

void	draw_tile(t_game *game, t_point pixel, int color)
{
	int	end_x;
	int	end_y;
	int	start_x;

	end_x = pixel.x + TILE_SIZE;
	end_y = pixel.y + TILE_SIZE;
	if (end_x > WIDTH)
		end_x = WIDTH;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	start_x = pixel.x;
	while (pixel.y < end_y)
	{
		pixel.x = start_x;
		while (pixel.x < end_x)
		{
			put_pixel(&game->img, pixel.x, pixel.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
}

void	draw_scaled_texture_tile(t_img *img, t_img *tex_img,
		t_point *start_pixel, int size)
{
	t_point		tex;
	t_pointf	step;
	int			i;
	int			j;
	int			color;

	step.x = (float)tex_img->width / size;
	step.y = (float)tex_img->height / size;
	i = 0;
	while (i < size && start_pixel->y + i < HEIGHT)
	{
		tex.y = (int)(i * step.y);
		j = 0;
		while (j < size && start_pixel->x + j < WIDTH)
		{
			tex.x = (int)(j * step.x);
			color = get_tex_pixel(tex_img, tex.x, tex.y);
			put_pixel(img, start_pixel->x + j, start_pixel->y + i, color);
			j++;
		}
		i++;
	}
}
