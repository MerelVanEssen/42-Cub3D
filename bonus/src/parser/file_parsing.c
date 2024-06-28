/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/13 18:06:56 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/20 20:32:03 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief goes through all lines and collect all data;
 * @param line double array to last line found in file;
 * @return error msg or NULL by success;
*/
static char	*get_map_attributes(t_cube *cube, int fd, char **line)
{
	char	attr_is_set[7];
	char	*err_msg;

	*line = get_next_line(fd);
	if (*line == NULL)
		return ("Error\nEmpty map file");
	ft_strlcpy(attr_is_set, "000000", 7);
	while (ft_strncmp(attr_is_set, "111111", 6) != 0 && line != NULL)
	{
		skip_empty_strings(line, fd);
		err_msg = set_one_attribute(cube, line, attr_is_set);
		if (err_msg != NULL)
			return (err_msg);
		*line = get_next_line(fd);
	}
	if (ft_strncmp(attr_is_set, "111111", 6) != 0)
		return ("Error\nCan't parse all map attributes");
	skip_empty_strings(line, fd);
	return (NULL);
}

/**
 * @brief seperates validation in diffend parts;
 * @param map_strings attributes and map in linked list;
 * @return string with error msg or NULL with success;
*/
static char	*process_file_strings(int fd, t_cube *cube, t_list **map_strings)
{
	char	*line;
	char	*err_msg;

	*map_strings = NULL;
	err_msg = get_map_attributes(cube, fd, &line);
	if (err_msg == NULL)
		err_msg = get_map_strings(fd, map_strings, cube, &line);
	if (err_msg != NULL)
		return (err_msg);
	skip_empty_strings(&line, fd);
	if (line == NULL)
		return (NULL);
	free(line);
	return ("Error\nNo lines allowed after map");
}

/**
 * @brief loads bonus textures: door, door_wall;
 * @return string with error msg or NULL with success;
*/
char	*load_bonus_images(t_cube *cube)
{
	cube->textures[DOOR] = mlx_load_png("textures/door.png");
	cube->textures[DOOR_WALL] = mlx_load_png("textures/door_wall.png");
	if (cube->textures[DOOR] == NULL || cube->textures[DOOR_WALL] == NULL)
		return ("Error\nCan't load door textures");
	return (NULL);
}

/**
 * @brief opens and validates the giving map and attributes, 
 * exits program by error;
 * @param filepath to the map;
*/
void	parse_map(t_cube *cube, char *filepath)
{
	int		fd;
	t_list	*map_strings;
	int		len;
	char	*err_msg;

	len = ft_strlen(filepath);
	if (len < 5 || ft_strncmp(filepath + len - 4, ".cub", 4) != 0)
		clean_and_exit(cube, 1, "Error\nFile extension should be .cub");
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		clean_and_exit(cube, 1, "Error\nCan't open file");
	err_msg = process_file_strings(fd, cube, &map_strings);
	close(fd);
	if (err_msg == NULL)
		err_msg = create_map(cube, map_strings);
	ft_lstclear(&map_strings, &free);
	if (err_msg == NULL)
		err_msg = validate_map(cube);
	if (err_msg == NULL)
		err_msg = load_bonus_images(cube);
	if (err_msg != NULL)
		clean_and_exit(cube, 1, err_msg);
}
