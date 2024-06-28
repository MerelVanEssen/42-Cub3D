/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_textures.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 11:57:27 by mvan-ess      #+#    #+#                 */
/*   Updated: 2024/06/25 20:21:32 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

/**
 * @brief gets alls textures for animation fire;
 * @return 0 by success, 1 by error;
*/
int	get_fire(t_sprite *sprite)
{
	sprite->fire[0] = mlx_load_png("textures/fire/fire0.png");
	if (!sprite->fire[0])
		return (1);
	sprite->fire[1] = mlx_load_png("textures/fire/fire1.png");
	if (!sprite->fire[1])
		return (1);
	sprite->fire[2] = mlx_load_png("textures/fire/fire2.png");
	if (!sprite->fire[2])
		return (1);
	sprite->fire[3] = mlx_load_png("textures/fire/fire3.png");
	if (!sprite->fire[3])
		return (1);
	sprite->fire[4] = mlx_load_png("textures/fire/fire4.png");
	if (!sprite->fire[4])
		return (1);
	sprite->fire[5] = mlx_load_png("textures/fire/fire5.png");
	if (!sprite->fire[5])
		return (1);
	return (0);
}

/**
 * @brief gets alls textures for animation ghost;
 * @return 0 by success, 1 by error;
*/
int	get_ghost(t_sprite *sprite)
{
	sprite->ghost[0] = mlx_load_png("textures/ghost/ghost0.png");
	if (!sprite->ghost[0])
		return (1);
	sprite->ghost[1] = mlx_load_png("textures/ghost/ghost1.png");
	if (!sprite->ghost[1])
		return (1);
	sprite->ghost[2] = mlx_load_png("textures/ghost/ghost2.png");
	if (!sprite->ghost[2])
		return (1);
	sprite->ghost[3] = mlx_load_png("textures/ghost/ghost3.png");
	if (!sprite->ghost[3])
		return (1);
	sprite->ghost[4] = mlx_load_png("textures/ghost/ghost4.png");
	if (!sprite->ghost[4])
		return (1);
	sprite->ghost[5] = mlx_load_png("textures/ghost/ghost5.png");
	if (!sprite->ghost[5])
		return (1);
	return (0);
}
