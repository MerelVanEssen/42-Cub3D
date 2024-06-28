/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 10:16:34 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 20:32:06 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief creates a new animation;
 * @param x x-coordinate of sprite;
 * @param y y-coordinate of sprite;
 * @param sort 0 for fire, 1 for ghost;
 * @return new t_anime or NULL if malloc fails;
*/
static t_anime	*new_anime(mlx_texture_t **png, int x, int y, int sort)
{
	t_anime	*new;

	new = malloc(sizeof(t_anime));
	if (!new)
		return (NULL);
	new->x = x + 0.5;
	new->y = y + 0.5;
	new->png = png;
	new->frames = 6;
	new->sort = sort;
	new->next = NULL;
	return (new);
}

/**
 * @brief makes sprite linked list with right animation;
 * @param x x-coordinate of sprite;
 * @param y y-coordinate of sprite;
 * @param sort 0 for fire, 1 for ghost;
 * @return 0 by succes, 1 by malloc fail
*/
static int	get_anime(t_sprite *sprite, int x, int y, int sort)
{
	t_anime	*current;

	if (sprite->anime == NULL)
	{
		if (sort == 0)
			sprite->anime = new_anime(sprite->fire, x, y, sort);
		else
			sprite->anime = new_anime(sprite->ghost, x, y, sort);
		if (!sprite->anime)
			return (1);
		return (0);
	}
	current = sprite->anime;
	while (current->next != NULL)
		current = current->next;
	if (sort == 0)
		current->next = new_anime(sprite->fire, x, y, sort);
	else
		current->next = new_anime(sprite->ghost, x, y, sort);
	if (!current->next)
		return (1);
	return (0);
}

/**
 * @brief search in map for sprite chars and makes an animation;
 * @param error changes in 1 if malloc fails;
*/
static void	get_amount(t_cube *cube, int *error)
{
	int	y;
	int	x;

	y = 0;
	while (*error == 0 && y < cube->map_height - 1)
	{
		x = 0;
		while (*error == 0 && x < cube->map_width - 1)
		{
			if (cube->map[y][x] == 'G' || cube->map[y][x] == 'F')
			{
				if (cube->map[y][x] == 'F')
					*error = get_anime(cube->sprite, x, y, 0);
				else
					*error = get_anime(cube->sprite, x, y, 1);
				cube->sprite->amount++;
				cube->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief makes a linked list of sprites and gives right textures;
 * @return 0 by success and 1 by error;
*/
int	get_sprite(t_cube *cube)
{
	int	error;

	error = 0;
	get_amount(cube, &error);
	if (error == 1)
		return (1);
	if (cube->sprite->amount == 0)
		return (0);
	if (get_fire(cube->sprite))
		return (delete_sprites(cube->sprite));
	if (get_ghost(cube->sprite))
		return (delete_sprites(cube->sprite));
	return (0);
}
