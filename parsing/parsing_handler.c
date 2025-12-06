/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-06 11:11:58 by jmehmy            #+#    #+#             */
/*   Updated: 2025-12-06 11:11:58 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_texture_line(t_game *game, char *line, t_counter *counter)
{
	if (counter->texture_count == 4)
	{
		destroy_textures(game);
		return (ft_error("Error: Only 4 textures paths are allowd"));
	}
	if (parse_texture_line(game, line) != 0)
		return (-1);
	counter->texture_count++;
	return (0);
}

void	free_rgb_textures(t_game *game, char *rgb_str)
{
	free(rgb_str);
	destroy_textures(game);
}

int	handle_color_line(t_game *game, char *line, t_counter *counter)
{
	if (counter->color_count == 2)
	{
		destroy_textures(game);
		return (ft_error("Error: Only 2 color are allowed"));
	}
	if (parse_color_line(game, line) != 0)
		return (-1);
	counter->color_count++;
	return (0);
}

int	handle_map_line(t_game *game, char *line, t_counter *counter)
{
	if (!counter->map_started)
		counter->map_started = 1;
	if (append_map_line(game, line, counter->map_line_index) != 0)
	{
		destroy_textures(game);
		return (1);
	}
	counter->map_line_index++;
	return (0);
}
