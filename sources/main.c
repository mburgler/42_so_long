/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:45:19 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 22:18:47 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_masterstruc	*init_masterstruc(char *map_file)
{
	t_masterstruc	*masterstruc;

	masterstruc = ft_calloc(1, sizeof(t_masterstruc));
	if (!masterstruc)
		error_message("Malloc failed\n", masterstruc);
	masterstruc->map = ft_calloc(1, sizeof(t_map));
	if (!masterstruc->map)
		error_message("Malloc failed\n", masterstruc);
	masterstruc->sucess = 0;
	masterstruc->moves = 1;
	masterstruc->map->map_player_count = 0;
	masterstruc->map->map_collectible_count = 0;
	masterstruc->map->map_exit_count = 0;
	init_map(map_file, masterstruc);
	masterstruc->map->enemy_count = 0;
	check_map(masterstruc);
	return (masterstruc);
}

int	main(int argc, char **argv)
{
	t_masterstruc	*masterstruc;
	int				wrongfile;

	if (argc == 1)
		error_message("Correct synopsis: ./so_long #mapname#\n", NULL);
	wrongfile = ft_mapformat_and_filechecker(argv[1]);
	if (argc != 2 || wrongfile == -1)
		error_message("Correct synopsis: ./so_long #mapname#\n", NULL);
	masterstruc = init_masterstruc(argv[1]);
	masterstruc->mlx = mlx_init();
	if (!masterstruc->mlx)
		error_message("Initialising MLX failed\n", NULL);
	xpm_to_image(masterstruc);
	masterstruc->win = mlx_new_window(masterstruc->mlx,
			masterstruc->img_pxl * masterstruc->map->map_width,
			masterstruc->img_pxl * masterstruc->map->map_height, "RED_FLAG");
	mlx_loop_hook(masterstruc->mlx, render_frame, masterstruc);
	mlx_hook(masterstruc->win, KeyPress, KeyPressMask, key_press, masterstruc);
	mlx_hook(masterstruc->win, DestroyNotify, NoEventMask, xpress, masterstruc);
	mlx_loop(masterstruc->mlx);
	return (0);
}
