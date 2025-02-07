/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 19:58:39 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 21:31:39 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
static void	draw_screen(t_cube *cube, t_wall *wall)
{
	uint32_t	x_y[2];
	t_direction	side;

	x_y[X] = 0;
	while (x_y[X] < cube->image->width)
	{
		wall->distance = raycasting(cube, x_y[X], &side);
		wall->wall_buf[x_y[X]] = wall->distance;
		describe_wall(wall, cube, side);
		x_y[Y] = 0;
		while (x_y[Y] < cube->image->height)
		{
			cube->tex_y = (int)wall->tex_pos;
			wall->tex_pos += wall->step;
			mlx_put_pixel(cube->image, x_y[X], x_y[Y],
				get_color(cube, x_y, wall, side));
			x_y[Y]++;
		}
		x_y[X]++;
	}
}

static void	draw(void *param)
{
	t_cube		*cube;
	t_wall		wall;

	cube = param;
	draw_screen(cube, &wall);
	order_sprites(cube, cube->pc->pos_x, cube->pc->pos_y);
	sort_sprites(cube);
	draw_sprites(cube, wall);
	if (cube->show_map == TRUE)
		draw_minimap(cube);
	change_timers(cube);
	cube->frames++;
	if (cube->frames == INT_MAX)
		cube->frames = 0;
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
	mlx_loop_hook(cube->mlx, &draw, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
}
