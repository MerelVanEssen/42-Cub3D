/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/20 14:52:15 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 18:08:53 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief checks if there is a '0' (floor) in a corner;
 * @return 1 if true, 0 if not;
*/
int	check_corner(t_cube *cube, int x, int y)
{
	if (x < 0 || x >= cube->map_width)
		return (0);
	if (y < 0 || y >= cube->map_height)
		return (0);
	if (cube->map[y][x] != '1' && cube->map[y][x] != ' ')
		return (1);
	return (0);
}

/**
 * @brief checks if a door is (only) placed between two walls;
 * @return 0 if correct, 1 if not placed correct;
*/
int	check_door(t_cube *cube, int x, int y)
{
	char	**map;

	map = cube->map;
	if (x == 0 || x == cube->map_width - 1)
		return (1);
	if (y == 0 || y == cube->map_height - 1)
		return (1);
	if (map[y - 1][x] != map[y + 1][x] || map[y][x - 1] != map[y][x + 1])
		return (1);
	if (map[y - 1][x] == '1' && map[y + 1][x] == '1' \
			&& map[y][x - 1] == '0' && map[y][x + 1] == '0')
		return (0);
	else if (map[y - 1][x] == '0' && map[y + 1][x] == '0' \
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
		return (0);
	return (1);
}
