/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:31:36 by alpetukh          #+#    #+#             */
/*   Updated: 2024/06/20 18:08:32 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
	EAST = 3
}	t_direction;

typedef struct s_minimap // bonus
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

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	char			**map;
	int				map_width;
	int				map_height;
	t_player		*pc;
	mlx_texture_t	*textures[4];
	int				floor_color;
	int				ceiling_color;
	double			cursor_x;
	int				tex_x;
	int				tex_y;
}	t_cube;

void	clean_and_exit(t_cube *cube, int code, char *err_msg);

void	run_game(t_cube *cube);
double	raycasting(t_cube *cube, uint32_t x, t_direction *side);

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

#endif
