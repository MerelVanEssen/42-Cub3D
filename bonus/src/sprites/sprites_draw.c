/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 11:23:41 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 20:31:03 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief scales the texture to choose the right pixel and gets /draw the color;
 * @param sp contains all the variables, nessacery for the math;
 * @param current sprite to draw;
 * @param x_y position where to draw on the screen;
*/
static void	draw_sprite(t_cube *cube, t_sp sp, t_anime *current, int x_y[2])
{
	int	frame;

	frame = cube->frame;
	sp.d = (x_y[Y]) * 256 - HEIGHT * 128 + sp.sprite_height * 128;
	sp.tex_y = ((sp.d * current->png[frame]->height) / sp.sprite_height) / 256;
	sp.color = get_texture_color(current->png[frame], sp.tex_y, sp.tex_x);
	if ((int)sp.color != -1)
		mlx_put_pixel(cube->image, x_y[X], x_y[Y], sp.color);
}

/**
 * @brief calculates where the sprite is on the screen;
 * @param sp contains all the variables, nessacery for the math;
 * @return int with start x position for drawing;
*/
static int	calculate_sprite_size(t_sp *sp)
{
	sp->sprite_height = abs((int)(HEIGHT / (sp->transform[Y])));
	sp->draw_start[Y] = -sp->sprite_height / 2 + HEIGHT / 2;
	if (sp->draw_start[Y] < 0)
		sp->draw_start[Y] = 0;
	sp->draw_stop[Y] = sp->sprite_height / 2 + HEIGHT / 2;
	if (sp->draw_stop[Y] >= HEIGHT)
		sp->draw_stop[Y] = HEIGHT - 1;
	sp->sprite_width = abs((int)(HEIGHT / (sp->transform[Y])));
	sp->draw_start[X] = -sp->sprite_width / 2 + sp->sprite_screen[X];
	if (sp->draw_start[X] < 0)
		sp->draw_start[X] = 0;
	sp->draw_stop[X] = sp->sprite_width / 2 + sp->sprite_screen[X];
	if (sp->draw_stop[X] >= WIDTH)
		sp->draw_stop[X] = WIDTH - 1;
	return (sp->draw_start[X]);
}

/**
 * @brief calculates relative distance, inverse of the determinant, transform it 
 * in a matrix and get the sprite postition;
 * @param sp contains all the variables, nessacery for the math;
 * @param x position of the sprite in the map;
 * @param y position of the sprite in the map;
 * @return int with start x position for drawing;
*/
static int	get_calculation(t_player *pc, t_sp *sp, double x, double y)
{
	sp->sprite[X] = x - pc->pos_x;
	sp->sprite[Y] = y - pc->pos_y;
	sp->inv_det = 1.0 / (pc->plane_x * pc->dir_y - pc->dir_x * pc->plane_y);
	sp->transform[X] = sp->inv_det * (pc->dir_y * sp->sprite[X]
			- pc->dir_x * sp->sprite[Y]);
	sp->transform[Y] = sp->inv_det * (-pc->plane_y * sp->sprite[X]
			+ pc->plane_x * sp->sprite[Y]);
	sp->sprite_screen[X] = (int)((WIDTH / 2)
			* (1 + sp->transform[X] / sp->transform[Y]));
	return (calculate_sprite_size(sp));
}

/**
 * @brief draws sprite one by one, back to front;
 * @param wall contains all wall distances of x;
*/
void	draw_sprites(t_cube *cube, t_wall wall)
{
	t_anime	*current;
	t_sp	sp;
	int		x_y[2];

	current = cube->sprite->anime;
	while (current)
	{
		cube->frame = cube->frames / SPRITE_SPEED % current->frames;
		x_y[X] = get_calculation(cube->pc, &sp, current->x, current->y);
		while (x_y[X] < sp.draw_stop[X])
		{
			sp.tex_x = (int)(256 * (x_y[X] - (-(sp.sprite_width) / 2 \
				+ sp.sprite_screen[X])) * current->png[cube->frame]->width)
				/ sp.sprite_width / 256;
			if (sp.transform[Y] > 0 && x_y[X] > 0 && x_y[X] < WIDTH
				&& sp.transform[Y] < wall.wall_buf[x_y[X]])
			{
				x_y[Y] = sp.draw_start[Y] - 1;
				while (++x_y[Y] < sp.draw_stop[Y])
					draw_sprite(cube, sp, current, x_y);
			}
			x_y[X]++;
		}
		current = current->next;
	}
}
