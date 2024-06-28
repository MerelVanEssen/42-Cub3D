/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 11:12:58 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 21:12:09 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	delete_sprites(t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (sprite->fire[i])
			mlx_delete_texture(sprite->fire[i]);
		if (sprite->ghost[i])
			mlx_delete_texture(sprite->ghost[i]);
		i++;
	}
	return (1);
}

static void	delete_anime(t_sprite *sprite)
{
	t_anime	*anime;

	while (sprite->anime != NULL)
	{
		anime = sprite->anime;
		sprite->anime = anime->next;
		free(anime);
	}
}

/**
 * @brief frees the t_cube struct
*/
void	free_cube_struct(t_cube *cube)
{
	int		i;
	t_door	*door;

	delete_anime(cube->sprite);
	delete_sprites(cube->sprite);
	while (cube->doors != NULL)
	{
		door = cube->doors;
		cube->doors = door->next;
		free(door);
	}
	if (cube->map != NULL)
	{
		i = 0;
		while (i < cube->map_height && cube->map[i] != NULL)
			free(cube->map[i++]);
		free(cube->map);
	}
	i = -1;
	while (++i < 6)
	{
		if (cube->textures[i] != NULL)
			mlx_delete_texture(cube->textures[i]);
	}
}
