/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-ess <mvan-ess@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 16:31:45 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/06/25 21:06:26 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief frees the t_cube struct
*/
static void	free_cube_struct(t_cube *cube)
{
	int	i;

	if (cube->map != NULL)
	{
		i = 0;
		while (i < cube->map_height && cube->map[i] != NULL)
			free(cube->map[i++]);
		free(cube->map);
	}
	i = -1;
	while (++i < 4)
	{
		if (cube->textures[i] != NULL)
			mlx_delete_texture(cube->textures[i]);
	}
}

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

int	main(int argc, char *argv[])
{
	t_cube		cube;
	t_player	pc;

	ft_bzero(&cube, sizeof(t_cube));
	if (argc != 2)
		clean_and_exit(&cube, 1, "Error\nOne argument 'filepath' required");
	cube.pc = &pc;
	parse_map(&cube, argv[1]);
	run_game(&cube);
	clean_and_exit(&cube, 0, NULL);
	return (0);
}
