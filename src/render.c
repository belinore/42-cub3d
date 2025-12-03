/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:08:14 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 16:08:15 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Out of bounds check can be removed later for performance
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		printf("put_pixel: coordinates out of bounds (%d, %d)\n", x, y);
		return ;
	}
	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixel_ptr + offset) = color;
}

void	new_img(t_game *vars)
{
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->img.img_ptr == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		destroy_display_and_exit(vars->mlx, "mlx_new_image failed\n");
	}
	vars->img.pixel_ptr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
}

void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y >= game->mouse_y)
				put_pixel(&game->img, x, y, game->textures.floor);
			else
				put_pixel(&game->img, x, y, game->textures.ceiling);
			x++;
		}
		y++;
	}
}

//Out of bounds check can be removed later for performance
int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
	{
		printf("get_tex_pixel: coordinates out of bounds (%d, %d)\n", x, y);
		return (0);
	}
	pixel = tex->pixel_ptr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	render_frame(t_game *game)
{
	double		fps;
	uint64_t	time_now;
	static long	total_frames;

	if (game->key_states.pause)
		return (0);
	time_now = get_time_in_ms();
	game->dt = (time_now - game->last_frame_time) / 1000.0;
	game->last_frame_time = time_now;
	handle_events(game);
	new_img(game);
	draw_ceiling_and_floor(game);
	raycasting(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	total_frames++;
	if (DEBUG_MODE && total_frames % 60 == 0)
	{
		fps = 1.0 / game->dt;
		printf("FPS: %.2f\n", fps);
	}
	return (0);
}
