/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:16:23 by belinore          #+#    #+#             */
/*   Updated: 2025/12/03 19:30:44 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include <stdint.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx_macos/mlx.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

# define DEBUG_MODE 1
# define WIDTH 1280//640
# define HEIGHT 720//400

# define MAX_RAY_LENGTH 1000
# define ROTATION_SPEED 2
# define MOVE_SPEED 2
# define MOUSE_SENSITIVITY 0.5
# define VERTICAL_GRIDLINE 0
# define HORIZONAL_GRIDLINE 1
# define PLAYER_RADIUS 0.1
# define MS_PER_FRAME 1600
# define PI 3.14159265358979323846

//COLORS
# define RED 0xFF0000
# define DARK_RED 0x800000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define BLUE 0x0000FF
# define DARK_BLUE 0x000080
# define YELLOW 0xFFDE21
# define GREEN 0x00FF00
# define LIGHT_GREY 0xD3D3D3
# define DARK_GREY 0x708090
# define BLUE_GREY 0x7393B3

//KEYCODES LINUX
# define ESC 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define P_KEY 112
# define ENTER_KEY 65293
# define BACKSPACE 65288

// // KEYCODES MACOS
// # define ESC 53
// # define W_KEY 13
// # define A_KEY 0
// # define S_KEY 1
// # define D_KEY 2
// # define LEFT_ARROW 123
// # define RIGHT_ARROW 124
// # define UP_ARROW 126
// # define DOWN_ARROW 125
// # define P_KEY 35
// # define ENTER_KEY 36
// # define BACKSPACE 51

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/* ************************************************************************** */
/*                                 IMAGE                                      */
/* ************************************************************************** */

typedef struct s_img
{
	void	*img_ptr;
	char    *pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* ************************************************************************** */
/*                                 POINTS                                     */
/* ************************************************************************** */

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_pointf
{
	double	x;
	double	y;
}	t_pointf;

/* ************************************************************************** */
/*                               TEXTURE PATHS                                */
/*                 (parser → stores .xpm file paths only)                     */
/* ************************************************************************** */

typedef struct s_tex_path
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
}	t_tex_path;

/* ************************************************************************** */
/*                          LOADED RENDER TEXTURES                            */
/*               (renderer → filled with mlx_xpm_file_to_image)              */
/* ************************************************************************** */

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		floor;		// RGB converted to int
	int		ceiling;
}	t_textures;

/* ************************************************************************** */
/*                                   COLOR                                    */
/*                                    (RGB)                                   */
/* ************************************************************************** */

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_counter
{
	int			texture_count;
	int			color_count;
	int			map_started;
	int			map_line_index;
}				t_counter;

/* ************************************************************************** */
/*                                  MAP DATA                                  */
/* ************************************************************************** */

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* ************************************************************************** */
/*                              PLAYER (FINAL)                                */
/*               (merged parser + renderer → raycasting ready)                */
/* ************************************************************************** */

typedef struct s_player
{
	int		map_x;      // current tile
	int		map_y;
	double	pos_x;      // precise position (float)
	double	pos_y;
	double	dir_x;      // direction vector
	double	dir_y;
	double	plane_x;    // camera plane vector
	double	plane_y;
	t_point	pixel;      // minimap pixel position
}	t_player;

/* ************************************************************************** */
/*                                KEY STATES                                  */
/* ************************************************************************** */

typedef struct s_keys
{
	int	move_forward;
	int	move_backward;
	int	strafe_left;
	int	strafe_right;
	int	rotate_left;
	int	rotate_right;
	int	pause;
}	t_keys;

/* ************************************************************************** */
/*                           WALL HIT (RAY RESULT)                            */
/* ************************************************************************** */

typedef struct s_wall
{
	int		map_tile_x;
	int		map_tile_y;
	double	hit_pos_x;;
	double	hit_pos_y;
	int		column;
	int		height;
	int		top_y;
	int		bottom_y;
	t_img	*texture;
	int		tex_x;
	int		tex_y;
}	t_wall;

/* ************************************************************************** */
/*                                 RAY DATA                                   */
/* ************************************************************************** */

typedef struct s_ray
{
	double	total_dist_x;
	double	total_dist_y;
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		hit_side;
	t_wall	wall;
}	t_ray;

/* ************************************************************************** */
/*                                  GAME                                      */
/*               (FINAL MASTER STRUCT — parser + renderer)                    */
/* ************************************************************************** */

typedef struct s_game
{
	/* MLX */
	void		*mlx;
	void		*window;
	t_img		img;

	/* Textures */
	t_tex_path	tex_path;	// From parser
	t_textures	textures;	// Loaded images from renderer

	/* Map + Player */
	t_map		map;
	t_player	player;

	/* Colors */
	t_color		floor_color;
	t_color		ceiling_color;

	/* Input */
	t_keys		key_states;

	/* Raycasting / Render Settings */
	double		fov;
	int			tile_size;
	double		camera_x[WIDTH];
	double		dist_to_camera_plane;
	t_ray		rays[WIDTH];

	/* Timing */
	uint64_t	last_frame_time;
	double		dt;

	/* Mouse */
	int			mouse_x;
	int			mouse_y;

}	t_game;

//main.c
void		destroy_display_and_exit(t_game *g, char *msg);

//init_mlx.c
void		load_texture_to_buffer(t_game *g, t_img *img, char *path);
void		init_textures(t_game *g);
void		init_hooks(t_game *g);
void		init_mlx(t_game *g);

//init_game.c
void		init_camera(t_game *g);
void		set_player_direction(t_game *g, char direction);
void		init_player(t_game *g);
void		init_game(t_game *g);

//events.c
int			close_window(t_game *g);
void		update_key_states(int keycode, t_keys *keys, int toggle);
int			key_handler(int keycode, t_game *g);
int			key_release_handler(int keycode, t_game *g);
int			mouse_move_handler(int x, int y, t_game *g);

//movement.c
t_pointf	get_new_position(t_game *g, double speed, int keycode);
int			is_valid_move(t_game *g, double x, double y);
void		move_player(t_game *g, double speed, int keycode);
void		rotate_player(t_game *g, double rot_speed_radians);
void		handle_events(t_game *g);

//render.c
void		put_pixel(t_img *img, int x, int y, int color);
void		new_img(t_game *vars);
void		draw_ceiling_and_floor(t_game *game);
int			get_tex_pixel(t_img *tex, int x, int y);
int			render_frame(t_game *vars);

//raycasting.c
void		move_to_next_gridline(t_ray *ray, int *map_x, int *map_y);
void		cast_ray(t_game *g, t_ray *ray);
void		calc_ray_direction(t_game *g, t_ray *ray, int column);
void		calc_dda_distances(t_ray *ray, t_player *player);
void		raycasting(t_game *g);

//raycasting2.c
t_img		*get_wall_texture(t_game *g, t_ray *ray);
void		draw_wall_slice(t_game *g, t_wall *wall);
void		calc_wall_height_and_texture(t_game *g, t_ray *ray, int column);

//minimap.c
void		raycasting_minimap(t_game *g);
void		draw_player(t_game *g);
void		draw_minimap_tile(t_game *g, t_point *pixel, int i, int j);
void		draw_minimap(t_game *g);

//utils.c
uint64_t	get_time_in_ms(void);
int			max(int n1, int n2);
int			iabs(int n);
double		scale_pixel(int unscaled_num, double new_min, double new_max,
				int old_max);

//draw_utils.c
void		draw_line(t_img *img, t_point p0, t_point p1, int color);
void		draw_circle(t_img *img, t_point center, int radius, int color);
void		draw_tile(t_game *game, t_point pixel, int color);
void		draw_scaled_texture_tile(t_img *img, t_img *tex_img,
				t_point *start_pixel, int size);


//parser
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