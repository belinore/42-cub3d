/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:53:54 by belinore          #+#    #+#             */
/*   Updated: 2025/12/03 19:06:28 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_to_buffer(t_game *g, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(g->mlx, path, &img->width,
			&img->height);
	if (!g->textures.north.img_ptr)
		destroy_display_and_exit(g, "Failed to load texture\n");
	img->pixel_ptr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

//test textures - to be replaced with parsed textures from file
//south_path = "textures/purple_stone.xpm"; -> higher res example
void	init_textures(t_game *g)
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;

	north_path = "textures/wolfenstein/eagle.xpm";
	south_path = "textures/wolfenstein/blue_stone.xpm";
	east_path = "textures/wolfenstein/red_brick.xpm";
	west_path = "textures/wolfenstein/grey_stone.xpm";
	load_texture_to_buffer(g, &g->textures.north, north_path);
	load_texture_to_buffer(g, &g->textures.south, south_path);
	load_texture_to_buffer(g, &g->textures.east, east_path);
	load_texture_to_buffer(g, &g->textures.west, west_path);
	g->textures.floor = DARK_BLUE;
	g->textures.ceiling = BLUE_GREY;
}

void	init_hooks(t_game *g)
{
	mlx_hook(g->window, ON_DESTROY, 1L << 2, close_window, g);
	mlx_hook(g->window, ON_KEYDOWN, 1L << 0, key_handler, g);
	mlx_hook(g->window, ON_MOUSEMOVE, 1L << 6, mouse_move_handler, g);
	mlx_hook(g->window, ON_KEYUP, 1L << 1, key_release_handler, g);
	mlx_loop_hook(g->mlx, render_frame, g);
}

void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		destroy_display_and_exit(g, "mlx_init failed\n");
	g->window = mlx_new_window(g->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!g->window)
		destroy_display_and_exit(g, "mlx_new_window failed\n");
	g->img.img_ptr = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img.img_ptr)
		destroy_display_and_exit(g, "mlx_new_image failed\n");
	g->img.pixel_ptr = mlx_get_data_addr(g->img.img_ptr, &g->img.bpp,
			&g->img.line_length, &g->img.endian);
}
