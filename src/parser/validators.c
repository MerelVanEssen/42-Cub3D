/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:16:35 by alpetukh          #+#    #+#             */
/*   Updated: 2024/06/20 16:14:24 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief validate path name if the file is .png;
 * @return 0 if not, 1 by success;
*/
t_bool	is_valid_image(char *path)
{
	int	len;

	if (path == NULL || *path == '\0')
		return (FALSE);
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".png", 4) != 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief checks row of map if surrounding by walls;
*/
static t_bool	is_valid_row(char *row, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (i < len && row[i] == ' ')
			i++;
		if (row[i] == '0')
			return (FALSE);
		while (i < len && row[i] != ' ')
			i++;
		if (row[i - 1] == '0')
			return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief checks if there is a '0' (floor) in a corner;
 * @return 1 if true, 0 if not;
*/
static int	check_corner(t_cube *cube, int x, int y)
{
	if (x < 0 || x >= cube->map_width)
		return (0);
	if (y < 0 || y >= cube->map_height)
		return (0);
	if (cube->map[y][x] == '0')
		return (1);
	return (0);
}

/**
 * @brief checks all corners of map if wall is complete;
 * @return error msg or NULL by success;
*/
static char	*check_corners(t_cube *cube)
{
	int	x;
	int	y;
	int	flag;

	flag = 0;
	y = -1;
	while (++y < cube->map_height)
	{
		x = -1;
		while (++x < cube->map_width)
		{
			if (cube->map[y][x] != ' ')
				continue ;
			flag += check_corner(cube, x - 1, y - 1);
			flag += check_corner(cube, x + 1, y - 1);
			flag += check_corner(cube, x - 1, y + 1);
			flag += check_corner(cube, x + 1, y + 1);
			if (flag > 0)
				return ("Error\nMap is invalid");
		}
	}
	return (NULL);
}

/**
 * @brief validates the map;
 * @return error msg or NULL by success;
*/
char	*validate_map(t_cube *cube)
{
	int		i;
	char	*row;
	t_bool	flag;

	i = 0;
	flag = TRUE;
	while (i < cube->map_height && flag == TRUE)
		flag = is_valid_row(cube->map[i++], cube->map_width);
	if (flag == FALSE)
		return ("Error\nMap is invalid");
	row = (char *)malloc(cube->map_height + 1);
	if (row == NULL)
		return ("Error\nMalloc error in validate_map");
	i = 0;
	while (i < cube->map_width && flag == TRUE)
	{
		copy_column(row, cube->map, i++, cube->map_height);
		flag = is_valid_row(row, cube->map_height);
	}
	free(row);
	if (flag == FALSE)
		return ("Error\nMap is invalid");
	return (check_corners(cube));
}
