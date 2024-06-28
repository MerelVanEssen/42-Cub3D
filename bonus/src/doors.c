/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doors.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/21 18:31:54 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 20:53:30 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*init_door(t_cube *cube, int x, int y)
{
	t_door	*door;

	if (check_door(cube, x, y) > 0)
		return ("Error\nMap is invalid: check_door");
	door = (t_door *)malloc(sizeof(t_door));
	if (door == NULL)
		return ("Error\nMalloc error in init_door");
	door->x = x;
	door->y = y;
	door->timer = 0;
	door->is_open = FALSE;
	door->next = cube->doors;
	cube->doors = door;
	return (NULL);
}

t_door	*get_door(t_cube *cube, int x, int y)
{
	t_door	*door;

	door = cube->doors;
	while (door != NULL)
	{
		if (door->x == x && door->y == y)
			return (door);
		door = door->next;
	}
	return (NULL);
}

void	change_timers(t_cube *cube)
{
	t_door	*door;

	if (cube->key_timer > 0)
		cube->key_timer -= 1;
	door = cube->doors;
	while (door != NULL)
	{
		if (door->timer > 0)
			door->timer -= 1;
		door = door->next;
	}
}

t_door	*get_players_door(t_cube *cube, int x, int y)
{
	if (fabs(cube->pc->dir_y) > fabs(cube->pc->dir_x))
	{
		if (cube->pc->dir_y > 0)
			y++;
		else
			y--;
	}
	else if (cube->pc->dir_x > 0)
		x++;
	else
		x--;
	if (cube->map[y][x] == 'D')
		return (get_door(cube, x, y));
	return (NULL);
}
