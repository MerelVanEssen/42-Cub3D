/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:35:30 by alpetukh          #+#    #+#             */
/*   Updated: 2024/06/20 16:15:09 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief takes direction and sets corresponding number;
 * @return int with corresponding number;
*/
static int	get_char_index(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ch)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

/**
 * @brief sets player position, dir, and plany;
*/
static void	init_pc(t_player *pc, int x, int y, int dir)
{
	const double	*preset;
	const double	presets[4][4] = {{0, 1, -0.66, 0}, {0, -1, 0.66, 0}, \
									{-1, 0, 0, -0.66}, {1, 0, 0, 0.66}};

	pc->pos_x = x + 0.5;
	pc->pos_y = y + 0.5;
	preset = presets[dir];
	pc->dir_x = preset[0];
	pc->dir_y = preset[1];
	pc->plane_x = preset[2];
	pc->plane_y = preset[3];
}

/**
 * @brief search for player in map and saves location/direction;
 * @return error msg or NULL by success;
*/
char	*find_pc(t_cube *cube, t_player *pc)
{
	int	x;
	int	y;
	int	dir;

	pc->pos_x = 0;
	x = -1;
	while (++x < cube->map_width)
	{
		y = -1;
		while (++y < cube->map_height)
		{
			dir = get_char_index("NSWE", cube->map[y][x]);
			if (dir == -1)
				continue ;
			if (pc->pos_x != 0)
				return ("Error\nSeveral players on the map");
			init_pc(pc, x, y, dir);
			cube->map[y][x] = '0';
		}
	}
	if (pc->pos_x == 0)
		return ("Error\nNo player on the map");
	return (NULL);
}
