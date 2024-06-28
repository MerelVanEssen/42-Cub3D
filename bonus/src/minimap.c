/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-ess <mvan-ess@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:13:41 by mvan-ess          #+#    #+#             */
/*   Updated: 2024/06/24 12:38:25 by mvan-ess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @return gives color nr depending on floor / wall
*/
static int	color_map(char c)
{
	if (c == '1')
		return (0x00000033);
	else if (c == 'D')
		return (0x00FF0022);
	return (0x006633FF);
}

/**
 * @brief draws the dir of view from player;
*/
static void	draw_line(t_cube *cube, t_minimap mm, int color, int weight)
{
	int	x;
	int	y;

	x = 0;
	while (x < weight)
	{
		y = 0;
		while (y < weight)
		{
			mlx_put_pixel(cube->image, mm.start_pc_x + x,
				mm.start_pc_y + y, color);
			y++;
		}
		x++;
	}
}

/**
 * @brief draws the player middle in the minimap and the dir of view;
*/
static void	draw_player(t_cube *cube, t_minimap mm)
{
	mm.start_pc_x = mm.size / 2 - 4;
	mm.start_pc_y = mm.size / 2 - 4;
	draw_line(cube, mm, 0xFF0000FF, 8);
	mm.start_pc_y += (cube->pc->dir_y * mm.start_pc_y / 20);
	mm.start_pc_x += (cube->pc->dir_x * mm.start_pc_x / 20);
	mm.start_pc_y += 2;
	mm.start_pc_x += 2;
	draw_line(cube, mm, 0xFFFFFFFF, 4);
}

/**
 * @brief calculates the map size and map part relative to the player;
 * @param mm pointer to store all the data of the minimap;
*/
static void	get_start_minimap(t_cube *cube, t_minimap *mm)
{
	if (WIDTH < HEIGHT)
		mm->size = WIDTH / 3;
	else
		mm->size = HEIGHT / 3;
	mm->start_map_x = cube->pc->pos_x - (mm->size / 2.0 / MM_PIXEL);
	mm->start_map_y = cube->pc->pos_y - (mm->size / 2.0 / MM_PIXEL);
}

/**
 * @brief draws the minimap and calculates where to start drawing;
*/
void	draw_minimap(t_cube *cube)
{
	t_minimap	mm;
	int			x;
	int			y;

	get_start_minimap(cube, &mm);
	y = 0;
	while (y < mm.size)
	{
		x = 0;
		while (x < mm.size)
		{
			mm.map_x = mm.start_map_x + ((float)x / MM_PIXEL);
			mm.map_y = mm.start_map_y + ((float)y / MM_PIXEL);
			if (mm.map_x >= 0 && mm.map_x < cube->map_width && mm.map_y >= 0
				&& mm.map_y < cube->map_height)
				mlx_put_pixel(cube->image, x, y,
					color_map(cube->map[(int)mm.map_y][(int)mm.map_x]));
			else
				mlx_put_pixel(cube->image, x, y, 0x0);
			x += 1;
		}
		y += 1;
	}
	draw_player(cube, mm);
}
