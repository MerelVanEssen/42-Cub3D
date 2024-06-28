/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_attributes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 21:20:11 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/20 19:00:50 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief get right path and load png in texture;
 * @param type corresponding direction of path to wall texture; 
 * @return error msg or NULL is success;
*/
static char	*set_wall_texture(t_cube *cube, char *line, int type)
{
	char	*path;

	path = ft_strtrim(line, " \n");
	if (path == NULL)
		return ("Error\nMalloc error in set_wall_texture");
	if (is_valid_image(path) == FALSE)
	{
		free(path);
		return ("Error\nTexture file extension should be .png");
	}
	cube->textures[type] = mlx_load_png(path);
	free(path);
	if (cube->textures[type] == NULL)
		return ("Error\nCan't load texture file");
	return (NULL);
}

/**
 * @brief validate line with numbers;
 * @param rgb saves colors;
 * @return 0 when success, -1 when error;
*/
static int	parse_colors(char *line, int rgb[3])
{
	int	i;
	int	num;

	i = 0;
	while (i < 3)
	{
		num = 0;
		while (*line == ' ')
			line++;
		if (ft_isdigit(*line) == 0)
			return (-1);
		while (ft_isdigit(*line) > 0 && num < 256)
			num = num * 10 + (*line++ - '0');
		if (num > 255 || (i < 2 && *line != ','))
			return (-1);
		if (i < 2 && *line == ',')
			line++;
		rgb[i++] = num;
	}
	while (*line == ' ')
		line++;
	if (*line != '\n')
		return (-1);
	return (0);
}

/**
 * @brief checks numbers for color of floor / ceiling and saves it;
 * @param type bigger than 3, ceiling or floor;
 * @return error msg or NULL by success;
*/
static char	*set_color_attr(t_cube *cube, char *line, int type)
{
	int	rgb[3];

	if (parse_colors(line, rgb) == -1)
		return ("Error\nColor attribute is invalid");
	if (type == 4)
		cube->floor_color = get_color_parser(rgb[0], rgb[1], rgb[2], 255);
	else
		cube->ceiling_color = get_color_parser(rgb[0], rgb[1], rgb[2], 255);
	return (NULL);
}

/**
 * @brief all aspects from the attributes and saves right value;
 * @param attr_is_set collection to save  when a attribute is found;
 * @return error msg or NULL by success;
*/
char	*set_one_attribute(t_cube *cube, char **line_ptr, char *attr_is_set)
{
	char	*line;
	int		type;
	char	*err_msg;

	if (*line_ptr == NULL)
		return ("Error\nCan't parse all map attributes");
	err_msg = NULL;
	line = *line_ptr;
	while (*line == ' ')
		line++;
	type = find_attr_type(line);
	if (type >= 0 && attr_is_set[type] == '1')
		err_msg = "Error\nMap attributes set twice";
	else if (type >= 0 && type <= 3)
		err_msg = set_wall_texture(cube, line + 2, type);
	else if (type > 3)
		err_msg = set_color_attr(cube, line + 1, type);
	free(*line_ptr);
	if (type == -1)
		return ("Error\nIncorrect attribute type");
	attr_is_set[type] = '1';
	return (err_msg);
}
