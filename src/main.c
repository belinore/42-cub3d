/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:03:53 by belinore          #+#    #+#             */
/*   Updated: 2025/12/03 13:53:08 by belinore         ###   ########.fr       */
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

void	destroy_display_and_exit(t_game *vars, char *msg)
{
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	if (vars->textures.north.img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures.north.img_ptr);
	if (vars->textures.south.img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures.south.img_ptr);
	if (vars->textures.east.img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures.east.img_ptr);
	if (vars->textures.south.img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures.west.img_ptr);
	if (vars->window)
		mlx_destroy_window(vars->mlx, vars->window);
	if (vars->mlx)
	{
		mlx_loop_end(vars->mlx);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (msg)
	{
		perror(msg);
		exit (1);
	}
	printf("Exiting...\n");
	exit (0);
}

int	main(void)
{
	static t_game	game;

	init_mlx(&game);
	init_game(&game);
	mlx_loop(game.mlx);
}
