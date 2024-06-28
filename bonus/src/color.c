/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:26:07 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/24 11:26:52 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief returns a color of a texture pixel with (tex_x, tex_y) coordinates;
 * @return int32_t with color;
*/
int32_t	get_texture_color(mlx_texture_t *tex, int tex_y, int tex_x)
{
	int	i;
	int	rgba[4];

	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	i = 4 * (tex->width * tex_y + tex_x);
	rgba[0] = tex->pixels[i];
	rgba[1] = tex->pixels[i + 1];
	rgba[2] = tex->pixels[i + 2];
	rgba[3] = tex->pixels[i + 3];
	if (rgba[3] == 0)
		return (-1);
	return (get_color_parser(rgba[0], rgba[1], rgba[2], rgba[3]));
}

/**
 * @brief checks which color, ceiling, floor or wall;
 * @return int with color;
*/
int	get_color(t_cube *cube, uint32_t x_y[2], t_wall *wall, t_direction side)
{
	if ((int)x_y[Y] < wall->y_start)
		return (cube->ceiling_color);
	if ((int)x_y[Y] > wall->y_stop)
		return (cube->floor_color);
	return (get_texture_color(cube->textures[side], cube->tex_y, cube->tex_x));
}
