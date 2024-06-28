/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 19:58:39 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 20:41:21 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief returns a color of a texture pixel with (tex_x, tex_y) coordinates;
 * @return int32_t with color;
*/
static int32_t	get_texture_color(mlx_texture_t *tex, t_cube *cube)
{
	int	i;
	int	rgba[4];

	if (cube->tex_y >= (int)tex->height)
		cube->tex_y = tex->height - 1;
	i = 4 * (tex->width * cube->tex_y + cube->tex_x);
	rgba[0] = tex->pixels[i];
	rgba[1] = tex->pixels[i + 1];
	rgba[2] = tex->pixels[i + 2];
	rgba[3] = tex->pixels[i + 3];
	return (get_color_parser(rgba[0], rgba[1], rgba[2], rgba[3]));
}

/**
 * @brief checks which color, ceiling, floor or wall;
 * @return int with color;
*/
int	get_color(t_cube *cube, uint32_t x_y[2], t_wall *wall, t_direction side)
{
	if ((int)x_y[Y] < wall->y_start)
		return (cube->ceiling_color);
	if ((int)x_y[Y] > wall->y_stop)
		return (cube->floor_color);
	return (get_texture_color(cube->textures[side], cube));
}

/**
 * @brief sets variables after wall calculation to determine right pixel/color;
*/
static void	describe_wall(t_wall *wall, t_cube *cube, t_direction side)
{
	uint32_t	tex_height;

	tex_height = cube->textures[side]->height;
	wall->height = (int)(cube->image->height / wall->distance);
	wall->y_start = ((int)cube->image->height - wall->height) / 2;
	wall->y_stop = ((int)cube->image->height + wall->height) / 2;
	wall->step = 1.0 * tex_height / (wall->y_stop - wall->y_start);
	wall->tex_pos = -wall->y_start * wall->step;
}

/**
 * @brief draws pixels on screen after calculation;
 * @param param void pointer to t_cube cube information;
*/
static void	draw_screen(void *param)
{
	t_cube		*cube;
	uint32_t	x_y[2];
	t_direction	side;
	t_wall		wall;

	cube = param;
	x_y[X] = 0;
	while (x_y[X] < cube->image->width)
	{
		wall.distance = raycasting(cube, x_y[X], &side);
		describe_wall(&wall, cube, side);
		x_y[Y] = 0;
		while (x_y[Y] < cube->image->height)
		{
			cube->tex_y = (int)wall.tex_pos;
			wall.tex_pos += wall.step;
			mlx_put_pixel(cube->image, x_y[X], x_y[Y],
				get_color(cube, x_y, &wall, side));
			x_y[Y]++;
		}
		x_y[X]++;
	}
}

/**
 * @brief start xserver and hooks;
*/
void	run_game(t_cube *cube)
{
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (cube->mlx == NULL)
		clean_and_exit(cube, 1, "Error\nmlx_init");
	cube->image = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (cube->image == NULL)
		clean_and_exit(cube, 2, "Error\nmlx_new_image");
	if (mlx_image_to_window(cube->mlx, cube->image, 0, 0) == -1)
		clean_and_exit(cube, 2, "Error\nmlx_image_to_window");
	mlx_loop_hook(cube->mlx, &handle_keys, cube);
	mlx_cursor_hook(cube->mlx, &handle_cursor, cube);
	mlx_loop_hook(cube->mlx, &draw_screen, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
}
