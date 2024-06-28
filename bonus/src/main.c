/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 16:31:45 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 21:30:45 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief clean program and exit program;
 * @param code exit code, bigger than 2 when closing window;
 * @param erro_msg string with error message;
*/
void	clean_and_exit(t_cube *cube, int code, char *err_msg)
{
	if (err_msg != NULL)
		ft_putendl_fd(err_msg, 2);
	free_cube_struct(cube);
	if (code >= 2)
	{
		mlx_close_window(cube->mlx);
		mlx_terminate(cube->mlx);
	}
	if (code > 0)
		exit(code);
}

void	cube_bzero(t_cube *cube, t_player *pc, t_sprite *sprite)
{
	ft_bzero(cube, sizeof(t_cube));
	ft_bzero(pc, sizeof(t_player));
	ft_bzero(sprite, sizeof(t_sprite));
	cube->show_map = TRUE;
	cube->pc = pc;
	cube->sprite = sprite;
}

int	main(int argc, char *argv[])
{
	t_cube		cube;
	t_player	pc;
	t_sprite	sprite;

	cube_bzero(&cube, &pc, &sprite);
	if (argc != 2)
		clean_and_exit(&cube, 1, "Error\nOne argument 'filepath' required");
	parse_map(&cube, argv[1]);
	if (get_sprite(&cube))
		clean_and_exit(&cube, 1, "Error\nSprite fault");
	run_game(&cube);
	clean_and_exit(&cube, 0, NULL);
	return (0);
}
