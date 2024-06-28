/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 15:29:04 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/20 17:07:09 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_delta_dist(t_math *m)
{
	if (m->ray_dir[X] == 0)
		m->delta_dist[X] = 1e30;
	else
		m->delta_dist[X] = fabs(1.0 / m->ray_dir[X]);
	if (m->ray_dir[Y] == 0)
		m->delta_dist[Y] = 1e30;
	else
		m->delta_dist[Y] = fabs(1.0 / m->ray_dir[Y]);
}

static void	find_next_line(t_math *m, double pos_x, double pos_y)
{
	if (m->ray_dir[X] < 0)
	{
		m->step[X] = -1;
		m->side_dist[X] = (pos_x - m->map[X]) * m->delta_dist[X];
	}
	else
	{
		m->step[X] = 1;
		m->side_dist[X] = (m->map[X] + 1.0 - pos_x) * m->delta_dist[X];
	}
	if (m->ray_dir[Y] < 0)
	{
		m->step[Y] = -1;
		m->side_dist[Y] = (pos_y - m->map[Y]) * m->delta_dist[Y];
	}
	else
	{
		m->step[Y] = 1;
		m->side_dist[Y] = (m->map[Y] + 1.0 - pos_y) * m->delta_dist[Y];
	}
}

static t_direction	find_wall(t_math *m)
{
	if (m->side_dist[X] < m->side_dist[Y])
	{
		m->side_dist[X] += m->delta_dist[X];
		m->map[X] += m->step[X];
		if (m->ray_dir[X] > 0)
			return (WEST);
		return (EAST);
	}
	m->side_dist[Y] += m->delta_dist[Y];
	m->map[Y] += m->step[Y];
	if (m->ray_dir[Y] > 0)
		return (NORTH);
	return (SOUTH);
}

static double	get_wall_distance(t_cube *cube, t_math *m, t_direction side)
{
	double	wall_dist;
	double	wall_x;

	if (side > 1)
	{
		wall_dist = m->side_dist[X] - m->delta_dist[X];
		wall_x = cube->pc->pos_y + wall_dist * m->ray_dir[Y];
	}
	else
	{
		wall_dist = m->side_dist[Y] - m->delta_dist[Y];
		wall_x = cube->pc->pos_x + wall_dist * m->ray_dir[X];
	}
	wall_x -= floor(wall_x);
	cube->tex_x = (int)(wall_x * cube->textures[side]->width);
	if ((side > 1 && m->ray_dir[X] < 0) || (side <= 1 && m->ray_dir[Y] > 0))
		cube->tex_x = cube->textures[side]->width - cube->tex_x - 1;
	return (wall_dist);
}

double	raycasting(t_cube *cube, uint32_t x, t_direction *side)
{
	t_math	m;
	int		hit;

	m.map[X] = (int)cube->pc->pos_x;
	m.map[Y] = (int)cube->pc->pos_y;
	m.camera_x = 2 * x / (double)cube->image->width - 1;
	m.ray_dir[X] = cube->pc->dir_x + cube->pc->plane_x * m.camera_x;
	m.ray_dir[Y] = cube->pc->dir_y + cube->pc->plane_y * m.camera_x;
	set_delta_dist(&m);
	find_next_line(&m, cube->pc->pos_x, cube->pc->pos_y);
	hit = 0;
	while (hit == 0)
	{
		*side = find_wall(&m);
		if (cube->map[m.map[Y]][m.map[X]] != '0')
			hit = 1;
	}
	return (get_wall_distance(cube, &m, *side));
}
