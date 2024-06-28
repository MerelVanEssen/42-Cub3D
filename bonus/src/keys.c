/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 08:00:27 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/24 20:00:15 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief calculate the new position of the player while moving ahead/back;
 * @param speed positive or negative speed of ahead/back direction;
*/
static void	move_straight(t_cube *cube, double speed)
{
	t_player	*pc;
	int			x_new;
	int			y_new;

	pc = cube->pc;
	x_new = (int)(pc->pos_x + 8 * pc->dir_x * speed);
	y_new = (int)(pc->pos_y + 8 * pc->dir_y * speed);
	if (can_go(cube, (int)pc->pos_y, x_new) == TRUE)
		pc->pos_x += (pc->dir_x * speed);
	if (can_go(cube, y_new, (int)pc->pos_x) == TRUE)
		pc->pos_y += (pc->dir_y * speed);
}

/**
 * @brief calculate the new position of the player while moving left/right;
 * @param speed positive or negative speed of left/right direction;
*/
static void	move_sideways(t_cube *cube, double speed)
{
	t_player	*pc;
	int			x_new;
	int			y_new;

	pc = cube->pc;
	x_new = (int)(pc->pos_x + 12 * pc->plane_x * speed);
	y_new = (int)(pc->pos_y + 12 * pc->plane_y * speed);
	if (can_go(cube, (int)pc->pos_y, x_new) == TRUE)
		pc->pos_x += (pc->plane_x * speed);
	if (can_go(cube, y_new, (int)pc->pos_x) == TRUE)
		pc->pos_y += (pc->plane_y * speed);
}

/**
 * @brief rotates the camera, change player plane and direction point;
 * @param rot positive or negative speed of rotating direction; 
*/
static void	rotate_camera(t_cube *cube, double rot)
{
	double	plane_x;
	double	dir_x;

	plane_x = cube->pc->plane_x * cos(rot) - cube->pc->plane_y * sin(rot);
	cube->pc->plane_y = cube->pc->plane_x * sin(rot) \
		+ cube->pc->plane_y * cos(rot);
	dir_x = cube->pc->dir_x * cos(rot) - cube->pc->dir_y * sin(rot);
	cube->pc->dir_y = cube->pc->dir_x * sin(rot)
		+ cube->pc->dir_y * cos(rot);
	cube->pc->plane_x = plane_x;
	cube->pc->dir_x = dir_x;
}

/**
 * @brief hook to register key movement;
*/
void	handle_keys(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
		move_straight(cube, SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
		move_straight(cube, -SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		move_sideways(cube, SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		move_sideways(cube, -SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		rotate_camera(cube, SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		rotate_camera(cube, -SPEED);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE))
		open_close_door(cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_M))
		hide_show_map(cube);
}

/**
 * @brief hook to register cursor movement;
*/
void	handle_cursor(double xpos, double ypos, void *param)
{
	t_cube	*cube;
	double	delta_x;

	cube = param;
	if (cube->cursor_x == xpos)
		return ;
	(void)ypos;
	delta_x = xpos - cube->cursor_x;
	cube->cursor_x = xpos;
	if (delta_x > 0)
		rotate_camera(cube, SPEED);
	else if (delta_x < 0)
		rotate_camera(cube, -SPEED);
}
