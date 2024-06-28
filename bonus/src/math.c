/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:29:04 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/26 13:21:16 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief calculate the distance from the ray between 2 raster lines;
 * @param m variables to save the calculations;
*/
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

/**
 * @brief goes to the first line and saves that distance;
 * @param m variables to save the calculations;
 * @param pos_x position player;
 * @param pos_y position player;
*/
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

/**
 * @brief increases the distance after a step in the lowest distance (x/y);
 * @param m variables to save the calculations;
 * @return t_direction with value of wallside;
*/
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

/**
 * @brief calculates the exact wall distance and the position in texture;
 * @param m variables to save the calculations;
 * @param side name of wall side that is hit;
 * @return wall high;
*/
static double	get_wall_distance(t_cube *cube, t_math *m, t_direction *side)
{
	double	wall_dist;
	double	wall_x;
	int		dir;

	dir = *side;
	check_door_texture(cube, m, side);
	if (*side == DOOR)
		return (m->door_dist);
	if (dir > 1)
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
	cube->tex_x = (int)(wall_x * cube->textures[*side]->width);
	if ((dir > 1 && m->ray_dir[X] < 0) || (dir <= 1 && m->ray_dir[Y] > 0))
		cube->tex_x = cube->textures[*side]->width - cube->tex_x - 1;
	return (wall_dist);
}

/**
 * @brief calculates the high of the wall that is hit in x from screen;
 * @param x position on screen to print;
 * @param side define direction of founded side;
*/
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
		hit = is_wall(cube, &m, *side);
	}
	return (get_wall_distance(cube, &m, side));
}
