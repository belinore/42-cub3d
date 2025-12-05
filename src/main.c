/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:03:53 by belinore          #+#    #+#             */
/*   Updated: 2025/12/03 19:09:34 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
To toggle between running in macOS and Linux

Linux:
1) check header cub3d.h to ensure Linux keycodes are uncommented 
	and Macos keycodes are commented
2) ensure mlx_loop_end and mlx_destroy_display are uncommented 
	in below function destroy_display_and_exit
MacOs:
1) check header cub3d.h to ensure Linux keycodes are uncommented 
	and Macos keycodes are commented
2) ensure mlx_loop_end and mlx_destroy_display are commented 
	in below function destroy_display_and_exit

3) ./configure in relevant mlx folder
4) Make as normal
*/

void	destroy_display_and_exit(t_game *g, char *msg)
{
	if (g->img.img_ptr)
		mlx_destroy_image(g->mlx, g->img.img_ptr);
	if (g->textures.north.img_ptr)
		mlx_destroy_image(g->mlx, g->textures.north.img_ptr);
	if (g->textures.south.img_ptr)
		mlx_destroy_image(g->mlx, g->textures.south.img_ptr);
	if (g->textures.east.img_ptr)
		mlx_destroy_image(g->mlx, g->textures.east.img_ptr);
	if (g->textures.south.img_ptr)
		mlx_destroy_image(g->mlx, g->textures.west.img_ptr);
	if (g->window)
		mlx_destroy_window(g->mlx, g->window);
	if (g->mlx)
	{
		mlx_loop_end(g->mlx);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	if (msg)
	{
		perror(msg);
		exit (1);
	}
	destroy_textures(g);
	free_map(g);
	printf("Exiting...\n");
	exit (0);
}

void	initialize_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = (t_color){50, 50, 50};
	game->ceiling_color = (t_color){135, 206, 235};
}

int	main(int argc, char **argv)
{
	static t_game	game;
	if (argc != 2)
	{
		return (ft_error("map.cub file is missing"), 1);
	}
	initialize_game(&game);
	if (start_parsing(&game, argv) != 0)
		return (1);
	init_mlx(&game);
	init_game(&game);
	mlx_loop(game.mlx);
}
