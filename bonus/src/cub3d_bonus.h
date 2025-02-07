/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 16:31:36 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 20:45:10 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

# define WIDTH 2400
# define HEIGHT 1600
# define SPEED 0.05
# define X 1
# define Y 0
# define MM_PIXEL 50
# define TIMER 20
# define SPRITE_SPEED 3

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_directions
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	DOOR = 4,
	DOOR_WALL = 5
}	t_direction;

typedef struct s_minimap
{
	int		size;
	double	start_map_x;
	double	start_map_y;
	double	map_x;
	double	map_y;
	int		start_pc_x;
	int		start_pc_y;
	int		color;
}	t_minimap;

typedef struct s_math
{
	double	camera_x;
	double	ray_dir[2];
	double	delta_dist[2];
	double	side_dist[2];
	double	door_dist;
	int		map[2];
	int		step[2];
}	t_math;

typedef struct s_wall
{
	double	distance;
	double	step;
	double	tex_pos;
	int		height;
	int		y_start;
	int		y_stop;
	double	wall_buf[WIDTH];
}	t_wall;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_door
{
	int				x;
	int				y;
	t_bool			is_open;
	int				timer;
	struct s_door	*next;
}	t_door;

typedef struct s_anime
{
	double			x;
	double			y;
	int				dist;
	mlx_texture_t	**png;
	int				frames;
	int				sort;
	struct s_anime	*next;
}	t_anime;

typedef struct s_sp
{
	double		sprite[2];
	double		transform[2];
	double		inv_det;
	int			sprite_screen[2];
	int			sprite_height;
	int			sprite_width;
	int			draw_start[2];
	int			draw_stop[2];
	int			tex_x;
	int			tex_y;
	int			d;
	uint32_t	color;
}	t_sp;

typedef struct s_sprite
{
	t_anime			*anime;
	mlx_texture_t	*fire[6];
	mlx_texture_t	*ghost[6];
	int				amount;
}	t_sprite;

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	char			**map;
	int				map_width;
	int				map_height;
	t_player		*pc;
	mlx_texture_t	*textures[6];
	int				floor_color;
	int				ceiling_color;
	double			cursor_x;
	int				tex_x;
	int				tex_y;
	int				frames;
	int				frame;
	t_door			*doors;
	t_sprite		*sprite;
	t_bool			show_map;
	int				key_timer;
}	t_cube;

void	clean_and_exit(t_cube *cube, int code, char *err_msg);
int		delete_sprites(t_sprite *sprite);
void	free_cube_struct(t_cube *cube);

void	run_game(t_cube *cube);
double	raycasting(t_cube *cube, uint32_t x, t_direction *side);
int32_t	get_texture_color(mlx_texture_t *tex, int tex_y, int tex_x);
int		get_color(t_cube *cube, uint32_t x_y[2], t_wall *wall,
			t_direction side);

// parser
void	parse_map(t_cube *cube, char *filepath);
char	*find_pc(t_cube *cube, t_player *pc);

char	*set_one_attribute(t_cube *cube, char **line_ptr, char *attr_is_set);

int32_t	get_color_parser(int32_t r, int32_t g, int32_t b, int32_t a);
t_bool	is_empty_string(char *line);
void	skip_empty_strings(char **line, int fd);
void	copy_column(char *row, char **map, int x, int len);
int		find_attr_type(char *line);

char	*create_map(t_cube *cube, t_list *map_strings);
char	*get_map_strings(int fd, t_list **map_strings, t_cube *cube,
			char **line);

t_bool	is_valid_image(char *path);
char	*validate_map(t_cube *cube);

// minimap
void	draw_minimap(t_cube *cube);

// keys
void	handle_cursor(double xpos, double ypos, void *param);
void	handle_keys(void *param);

int		check_corner(t_cube *cube, int x, int y);
int		check_door(t_cube *cube, int x, int y);

// doors
char	*init_door(t_cube *cube, int x, int y);
t_door	*get_door(t_cube *cube, int x, int y);
void	change_timers(t_cube *cube);
t_door	*get_players_door(t_cube *cube, int x, int y);

void	open_close_door(t_cube *cube);
void	hide_show_map(t_cube *cube);
void	check_door_texture(t_cube *cube, t_math *m, t_direction *side);

t_bool	can_go(t_cube *cube, int y, int x);
int		is_wall(t_cube *cube, t_math *m, t_direction side);

//sprites
void	draw_sprites(t_cube *cube, t_wall wall);
void	sort_sprites(t_cube *cube);
void	order_sprites(t_cube *cube, int x, int y);

int		get_sprite(t_cube *cube);
void	position_anime(t_cube *cube);
int		check_empty_space(t_cube *cube, int x, int y);
int		count_posibilities(t_cube *cube);
int		get_ghost(t_sprite *sprite);
int		get_fire(t_sprite *sprite);
#endif
