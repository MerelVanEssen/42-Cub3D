/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_sort.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 11:21:09 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 20:32:29 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief calculates the distance from sprite to player before order;
 * @param x position player;
 * @param y position player;
*/
void	order_sprites(t_cube *cube, int x, int y)
{
	t_anime		*current;

	current = cube->sprite->anime;
	while (current)
	{
		current->dist = ((x - current->x) * (x - current->x)
				+ (y - current->y) * (y - current->y));
		current = current->next;
	}
}

/**
 * @brief swaps all information from sprites;
*/
static void	swap_sprites(t_anime **sprite1, t_anime **sprite2)
{
	double			tmp;
	mlx_texture_t	**img;
	double			dist;

	tmp = (*sprite1)->x;
	(*sprite1)->x = (*sprite2)->x;
	(*sprite2)->x = tmp;
	tmp = (*sprite1)->y;
	(*sprite1)->y = (*sprite2)->y;
	(*sprite2)->y = tmp;
	dist = (*sprite1)->dist;
	(*sprite1)->dist = (*sprite2)->dist;
	(*sprite2)->dist = dist;
	img = (*sprite1)->png;
	(*sprite1)->png = (*sprite2)->png;
	(*sprite2)->png = img;
}

/**
 * @brief bubblesort to sort by distance, far to close;
*/
void	sort_sprites(t_cube *cube)
{
	t_anime		*current;
	int			swap;

	swap = 1;
	while (swap)
	{
		current = cube->sprite->anime;
		swap = 0;
		while (current)
		{
			if (current->next && current->dist < current->next->dist)
			{
				swap_sprites(&current, &current->next);
				swap = 1;
			}
			current = current->next;
		}
	}
}
