/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:17:08 by alpetukh          #+#    #+#             */
/*   Updated: 2024/06/20 15:44:59 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief checks direction of wall texture;
 * @return type of direction, -1 when not found;
*/
int	find_attr_type(char *line)
{
	const char	attrs[6][3] = {"NO\0", "SO\0", "WE\0", "EA\0", "F\0", "C\0"};
	int			type;

	type = 0;
	while (type < 6)
	{
		if (ft_strncmp(line, attrs[type], ft_strlen(attrs[type])) == 0)
			return (type);
		type++;
	}
	return (-1);
}

/**
 * @brief convert rgb to hex;
*/
int32_t	get_color_parser(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief checks if string is empty;
 * @return 1 if empty, 0 if not;
*/
t_bool	is_empty_string(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\n' || *line == '\0')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief goes through file when empty line;
*/
void	skip_empty_strings(char **line, int fd)
{
	while (*line != NULL)
	{
		if (is_empty_string(*line) == FALSE)
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
}

/**
 * @brief copies the column before checking;
*/
void	copy_column(char *row, char **map, int x, int len)
{
	int	y;

	y = 0;
	while (y < len)
	{
		row[y] = map[y][x];
		y++;
	}
	row[len] = '\0';
}
