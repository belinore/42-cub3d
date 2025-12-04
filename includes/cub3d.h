#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Holds the 2D map (like rows of the map), size info also inside (width,
	height)
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

// Holds player position and where player is looking in the game
typedef struct s_player
{
	double		position_x;
	double		position_y;
	double		direction_x;
	double		direction_y;
	double		camera_x;
	double		camera_y;
}				t_player;

// Holds 4 wall image file paths (north, south, west, east)
typedef struct s_texture
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
}				t_texture;

// Helps to count textures, colors and map lines while reading file
typedef struct s_counter
{
	int			texture_count;
	int			color_count;
	int			map_started;
	int			map_line_index;
}				t_counter;

// Holds RGB color numbers (0–255) for floor or sky
typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

// Main that keeps map, player, textures and screen connection
typedef struct s_game
{
	void		*mlx;
	void		*wid;
	int			win_width;
	int			win_height;
	t_texture	tex;
	t_map		map;
	t_player	player;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_game;

void			initialize_game(t_game *game);
int				start_parsing(t_game *game, char **argv);
int				handle_line(t_game *game, char *line, t_counter *counter);
int				is_valid_cub_file(char **argv);
int				validate_map(t_game *game);

int				load_cub_file(t_game *game, const char *path);
int				read_cub_lines(t_game *game, int fd, t_counter *counter);
int				parse_single_line(t_game *game, char *line, t_counter *counter);
int				validate_parsing_completion(t_game *game, t_counter *counter);
int				check_valid_chars(t_game *game);

int				check_map_closed(t_game *game);
int				validate_and_store_player(t_game *game);

int				parse_color_line(t_game *game, char *line);

int				handle_map_line(t_game *game, char *line, t_counter *counter);
int				handle_color_line(t_game *game, char *line, t_counter *counter);
int				handle_texture_line(t_game *game, char *line,
					t_counter *counter);

int				append_map_line(t_game *game, char *line, int line_index);
int				parse_texture_line(t_game *game, char *line);

int				ft_error(char *message);
void			destroy_textures(t_game *game);
void			free_split(char **arr);
void			*gnl_free(void *str);
void			free_map(t_game *game);
void			free_rgb_textures(t_game *game, char *rgb_str);

#endif
