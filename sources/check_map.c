/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:10 by matteobuerg       #+#    #+#             */
/*   Updated: 2023/05/09 20:10:51 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_walls(t_masterstruc *masterstruc)
{
	int	i;
	int	j;

	j = 0;
	while (masterstruc->map->map[j])
	{
		i = 0;
		while (masterstruc->map->map[j][i])
		{
			if (j == 0 || j == masterstruc->map->map_height - 1)
			{
				if (masterstruc->map->map[j][i] != '1')
					error_message("Map not surrounded by walls", masterstruc);
			}
			if (i == 0 || i == masterstruc->map->map_width - 1)
			{
				if (masterstruc->map->map[j][i] != '1')
					error_message("Map not surrounded by walls", masterstruc);
			}
			i++;
		}
		j++;
	}
}

void	check_chars(t_masterstruc *masterstruc)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	while (j < masterstruc->map->map_height)
	{
		i = 0;
		while (i < masterstruc->map->map_width)
		{
			x = 0;
			while (masterstruc->map->map[j][i] != "01CEPX"[x])
			{
				if (!"01CEPX"[x])
					error_message("Forbidden character", masterstruc);
				x++;
			}
			count_chars("01CEPX"[x], masterstruc, 0);
			i++;
		}
		j++;
	}
	count_chars("01CEPX"[x], masterstruc, 1);
}

void	count_chars(char c, t_masterstruc *msc, int done_map)
{
	if (c == 'P')
		msc->map->map_player_count++;
	if (c == 'E')
		msc->map->map_exit_count++;
	if (c == 'C')
		msc->map->map_collectible_count++;
	if (c == 'X')
		msc->map->enemy_count++;
	if (done_map == 1)
	{
		if (msc->map->map_player_count != 1)
			error_message("Number of players is wrong", msc);
		if (msc->map->map_exit_count != 1)
			error_message("Number of exits is wrong", msc);
		if (msc->map->map_collectible_count < 1)
			error_message("Number of collectibles is wrong", msc);
	}
}

void	check_map(t_masterstruc *msc)
{
	int	j;

	j = 0;
	while (msc->map->map[j] && j < msc->map->map_height)
	{
		if (ft_strlen(msc->map->map[j]) != (size_t)msc->map->map_width)
			error_message("Map Error: Lines are different length", msc);
		j++;
	}
	check_walls(msc);
	check_chars(msc);
	position_player(msc);
	flood_fill(msc);
}
