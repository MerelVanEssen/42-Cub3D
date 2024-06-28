/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/21 16:43:42 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/24 20:04:55 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	open_close_door(t_cube *cube)
{
	int		x;
	int		y;
	t_door	*door;

	x = (int)cube->pc->pos_x;
	y = (int)cube->pc->pos_y;
	if (cube->map[y][x] == 'D')
		return ;
	door = get_players_door(cube, x, y);
	if (door == NULL || door->timer > 0)
		return ;
	door->is_open = !door->is_open;
	door->timer = TIMER;
}

void	hide_show_map(t_cube *cube)
{
	if (cube->key_timer > 0)
		return ;
	cube->show_map = !cube->show_map;
	cube->key_timer = 10;
}
