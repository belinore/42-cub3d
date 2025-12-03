/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:42:48 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 15:42:50 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *vars)
{
	destroy_display_and_exit(vars, NULL);
	return (0);
}

void	update_key_states(int keycode, t_keys *keys, int toggle)
{
	if (keycode == W_KEY || keycode == UP_ARROW)
		keys->move_forward = toggle;
	else if (keycode == S_KEY || keycode == DOWN_ARROW)
		keys->move_backward = toggle;
	else if (keycode == D_KEY)
		keys->strafe_right = toggle;
	else if (keycode == A_KEY)
		keys->strafe_left = toggle;
	else if (keycode == LEFT_ARROW)
		keys->rotate_left = toggle;
	else if (keycode == RIGHT_ARROW)
		keys->rotate_right = toggle;
}

int	key_handler(int keycode, t_game *game)
{
	if (keycode == P_KEY)
		game->key_states.pause = !game->key_states.pause;
	else if (keycode == ESC)
		destroy_display_and_exit(game, NULL);
	else
		update_key_states(keycode, &game->key_states, 1);
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	update_key_states(keycode, &game->key_states, 0);
	return (0);
}

int	mouse_move_handler(int x, int y, t_game *game)
{
	int		dx;
	double	rot_speed;

	if (game->key_states.pause || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	game->mouse_y = HEIGHT - y;
	dx = x - game->mouse_x;
	if (dx == 0)
		return (0);
	rot_speed = dx * MOUSE_SENSITIVITY;
	rotate_player(game, rot_speed);
	if (x == 0)
		game->mouse_x = x + 7;
	else if (x == WIDTH - 1)
		game->mouse_x = x - 7;
	else
		game->mouse_x = x;
	return (0);
}
