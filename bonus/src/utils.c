/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/21 17:10:33 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 20:43:13 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool	can_go(t_cube *cube, int y, int x)
{
	t_door	*door;

	if (cube->map[y][x] == '0')
		return (TRUE);
	if (cube->map[y][x] == 'D')
	{
		door = get_door(cube, x, y);
		if (door->is_open == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

static int	is_door(t_cube *cube, t_math *m, t_direction side, t_door *door)
{
	double	wall_x;

	if (side > 1)
	{
		m->door_dist = m->side_dist[X] - 0.5 * m->delta_dist[X];
		if (m->door_dist >= m->side_dist[Y])
			return (0);
		wall_x = cube->pc->pos_y + m->door_dist * m->ray_dir[Y];
	}
	else
	{
		m->door_dist = m->side_dist[Y] - 0.5 * m->delta_dist[Y];
		if (m->door_dist >= m->side_dist[X])
			return (0);
		wall_x = cube->pc->pos_x + m->door_dist * m->ray_dir[X];
	}
	wall_x -= floor(wall_x);
	if (door->timer > 0 && door->is_open == TRUE)
		wall_x += (double)(door->timer) / TIMER - 1;
	else if (door->timer > 0)
		wall_x -= (double)(door->timer) / TIMER;
	cube->tex_x = (int)(wall_x * cube->textures[DOOR]->width);
	if (door->timer == 0 || wall_x > 0)
		return (1);
	return (0);
}

int	is_wall(t_cube *cube, t_math *m, t_direction side)
{
	t_door	*door;

	if (cube->map[m->map[Y]][m->map[X]] == '1')
		return (1);
	if (cube->map[m->map[Y]][m->map[X]] == 'D')
	{
		door = get_door(cube, m->map[X], m->map[Y]);
		if (door->is_open == FALSE || door->timer > 0)
			return (is_door(cube, m, side, door));
	}
	return (0);
}

void	check_door_texture(t_cube *cube, t_math *m, t_direction *side)
{
	int	x;
	int	y;

	x = m->map[X];
	y = m->map[Y];
	if (cube->map[y][x] == 'D')
	{
		*side = DOOR;
		return ;
	}
	if (*side > 1)
		x -= m->step[X];
	else
		y -= m->step[Y];
	if (cube->map[y][x] == 'D')
		*side = DOOR_WALL;
}
