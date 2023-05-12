/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ma_boi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:19:01 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/09 20:10:40 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_ma_boi(t_masterstruc *masterstruc)
{
	int	i;

	i = 0;
	if (masterstruc != NULL)
	{
		if (masterstruc->map != NULL)
		{
			if (masterstruc->map->map != NULL)
			{
				while (masterstruc->map->map[i])
				{
					free(masterstruc->map->map[i]);
					i++;
				}
				free(masterstruc->map->map);
			}
			free(masterstruc->map);
		}
		free_ma_mlx(masterstruc);
		free(masterstruc);
	}
	exit(1);
}

void	free_ma_mlx(t_masterstruc *masterstruc)
{
	if (masterstruc->img)
	{
		if (masterstruc->img->coll)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->coll);
		if (masterstruc->img->enemy)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->enemy);
		if (masterstruc->img->floor)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->floor);
		if (masterstruc->img->goal_off)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->goal_off);
		if (masterstruc->img->goal_on)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->goal_on);
		if (masterstruc->img->player)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->player);
		if (masterstruc->img->wall)
			mlx_destroy_image(masterstruc->mlx, masterstruc->img->wall);
		free(masterstruc->img);
	}
	if (masterstruc->mlx)
	{
		if (masterstruc->win)
			mlx_destroy_window(masterstruc->mlx, masterstruc->win);
		mlx_destroy_display(masterstruc->mlx);
		free(masterstruc->mlx);
	}
}
