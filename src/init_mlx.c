/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:53:54 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 15:53:56 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_to_buffer(t_game *game, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!game->textures.north.img_ptr)
		destroy_display_and_exit(game, "Failed to load texture\n");
	img->pixel_ptr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

//test textures - to be replaced with parsed textures from file
//south_path = "textures/purple_stone.xpm"; -> higher res example
void	init_textures(t_game *game)
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;

	north_path = "textures/wolfenstein/eagle.xpm";
	south_path = "textures/wolfenstein/blue_stone.xpm";
	east_path = "textures/wolfenstein/red_brick.xpm";
	west_path = "textures/wolfenstein/grey_stone.xpm";
	load_texture_to_buffer(game, &game->textures.north, north_path);
	load_texture_to_buffer(game, &game->textures.south, south_path);
	load_texture_to_buffer(game, &game->textures.east, east_path);
	load_texture_to_buffer(game, &game->textures.west, west_path);
	game->textures.floor = DARK_BLUE;
	game->textures.ceiling = BLUE_GREY;
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->window, ON_DESTROY, 1L << 2, close_window, game);
	mlx_hook(game->window, ON_KEYDOWN, 1L << 0, key_handler, game);
	mlx_hook(game->window, ON_MOUSEMOVE, 1L << 6, mouse_move_handler, game);
	mlx_hook(game->window, ON_KEYUP, 1L << 1, key_release_handler, game);
	mlx_loop_hook(game->mlx, render_frame, game);
}

void	init_mlx(t_game *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		destroy_display_and_exit(vars, "mlx_init failed\n");
	vars->window = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!vars->window)
		destroy_display_and_exit(vars, "mlx_new_window failed\n");
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img.img_ptr)
		destroy_display_and_exit(vars, "mlx_new_image failed\n");
	vars->img.pixel_ptr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
}
