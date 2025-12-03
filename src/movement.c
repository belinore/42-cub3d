/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:05:02 by belinore          #+#    #+#             */
/*   Updated: 2025/12/02 16:05:03 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pointf	get_new_position(t_game *game, double speed, int keycode)
{
	t_pointf	new;

	speed *= game->dt;
	if (keycode == W_KEY || keycode == UP_ARROW)
	{
		new.x = game->player.pos_x + game->player.dir_x * speed;
		new.y = game->player.pos_y + game->player.dir_y * speed;
	}
	else if (keycode == S_KEY || keycode == DOWN_ARROW)
	{
		new.x = game->player.pos_x - game->player.dir_x * speed;
		new.y = game->player.pos_y - game->player.dir_y * speed;
	}
	if (keycode == D_KEY)
	{
		new.x = game->player.pos_x + game->player.plane_x * speed;
		new.y = game->player.pos_y + game->player.plane_y * speed;
	}
	else if (keycode == A_KEY)
	{
		new.x = game->player.pos_x - game->player.plane_x * speed;
		new.y = game->player.pos_y - game->player.plane_y * speed;
	}
	return (new);
}

int	is_valid_move(t_game *game, double x, double y)
{
	double	r;

	r = PLAYER_RADIUS;
	if (game->map[(int)(y + r)][(int)(x + r)] == '1' || game->map[(int)(y
			+ r)][(int)(x - r)] == '1' || game->map[(int)(y - r)][(int)(x
			+ r)] == '1' || game->map[(int)(y - r)][(int)(x - r)] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game, double speed, int keycode)
{
	t_pointf	new;

	new = get_new_position(game, speed, keycode);
	if (new.x < 0 || new.x >= game->map_width || new.y < 0
		|| new.y >= game->map_height)
		return ;
	if (is_valid_move(game, new.x, game->player.pos_y))
	{
		game->player.pos_x = new.x;
		game->player.map_x = (int)new.x;
		game->player.pixel.x = (int)(new.x * TILE_SIZE);
	}
	if (is_valid_move(game, game->player.pos_x, new.y))
	{
		game->player.pos_y = new.y;
		game->player.map_y = (int)new.y;
		game->player.pixel.y = (int)(new.y * TILE_SIZE);
	}
}

void	rotate_player(t_game *game, double rot_speed_radians)
{
	double		old_dir_x;
	double		old_plane_x;
	double		cos_angle;
	double		sin_angle;
	t_player	*player;

	player = &game->player;
	rot_speed_radians *= game->dt;
	cos_angle = cos(rot_speed_radians);
	sin_angle = sin(rot_speed_radians);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

void	handle_events(t_game *game)
{
	if (game->key_states.move_forward)
		move_player(game, MOVE_SPEED, W_KEY);
	if (game->key_states.move_backward)
		move_player(game, MOVE_SPEED, S_KEY);
	if (game->key_states.strafe_right)
		move_player(game, MOVE_SPEED, D_KEY);
	if (game->key_states.strafe_left)
		move_player(game, MOVE_SPEED, A_KEY);
	if (game->key_states.rotate_right)
		rotate_player(game, ROTATION_SPEED);
	if (game->key_states.rotate_left)
		rotate_player(game, -ROTATION_SPEED);
}
