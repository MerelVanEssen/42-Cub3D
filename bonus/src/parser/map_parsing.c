/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:34:46 by alpetukh          #+#    #+#             */
/*   Updated: 2024/06/24 15:43:08 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief creates a new node and ands to the back;
 * @return 0 by succes, 1 by malloc fail;
*/
static int	add_map_string(t_list **map_strings, char *line, int *len)
{
	t_list	*new_node;

	new_node = ft_lstnew(line);
	if (new_node == NULL)
	{
		free(line);
		return (1);
	}
	ft_lstadd_back(map_strings, new_node);
	*len += 1;
	return (0);
}

/**
 * @brief copys the mapline;
 * @return copied line or NULL if malloc fails;
*/
static char	*create_map_line(char *src, int len)
{
	char	*line;
	int		i;

	line = (char *)malloc(len + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	line[len] = '\0';
	while (i < len && src[i] != '\n' && src[i] != '\0')
	{
		line[i] = src[i];
		i++;
	}
	while (i < len)
		line[i++] = ' ';
	return (line);
}

/**
 * @brief creates a map with lines from linked list;
 * @return error msg or NULL by success;
*/
char	*create_map(t_cube *cube, t_list *map_strings)
{
	int		i;
	char	*line;

	cube->map = (char **)malloc(cube->map_height * sizeof(char *));
	if (cube->map == NULL)
		return ("Error\nMalloc error create_map");
	i = 0;
	while (i < cube->map_height)
	{
		line = create_map_line((char *)map_strings->content, cube->map_width);
		cube->map[i++] = line;
		if (line == NULL)
			return ("Error\nMalloc error create_map");
		map_strings = map_strings->next;
	}
	return (find_pc(cube, cube->pc));
}

/**
 * @brief validate line of map on char and width;
 * @param width pointer to save the highest founded width;
 * @return 0 by error, 1 by succes;
*/
static t_bool	is_map_string(char *line, int *width)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("01NSWEDFG \n", line[i]) == NULL)
			return (FALSE);
		if (i >= *width && line[i] != ' ' && line[i] != '\n')
			*width = i + 1;
		i++;
	}
	return (TRUE);
}

/**
 * @brief creates a linked list with file information;
 * @return error msg or NULL by success;
*/
char	*get_map_strings(int fd, t_list **map_strings, t_cube *cube,
						char **line)
{
	if (*line == NULL)
		return ("Error\nEmpty map");
	while (*line != NULL && is_empty_string(*line) == FALSE)
	{
		if (add_map_string(map_strings, *line, &cube->map_height) == 1)
			return ("Error\nMalloc error add_map_string");
		if (is_map_string(*line, &cube->map_width) == FALSE)
			return ("Error\nMap line or char is incorrect");
		*line = get_next_line(fd);
	}
	if (cube->map_height < 3 || cube->map_width < 3)
		return ("Error\nMap is too small");
	return (NULL);
}
