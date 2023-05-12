/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:56:45 by matteobuerg       #+#    #+#             */
/*   Updated: 2023/05/09 22:19:02 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

//Chars 01CEPX

void	fill(char **flood_map, int y, int x)
{
	if (flood_map[y][x] == '1' || flood_map[y][x] == 'X'
		|| flood_map[y][x] == 'F')
		return ;
	flood_map[y][x] = 'F';
	fill(flood_map, y - 1, x);
	fill(flood_map, y + 1, x);
	fill(flood_map, y, x - 1);
	fill(flood_map, y, x + 1);
}

void	check_flooded_map(t_masterstruc *masterstruc, char **flood_map)
{
	int	i;
	int	j;

	j = 0;
	while (j < masterstruc->map->map_height)
	{
		i = 0;
		while (i < masterstruc->map->map_width)
		{
			if (flood_map[j][i] == 'C' || flood_map[j][i] == 'E')
			{
				free_floodmap(flood_map);
				error_message("Exit/Coins can't be reached", masterstruc);
			}
			i++;
		}
		j++;
	}
}

void	flood_fill(t_masterstruc *msc)
{
	char	**flood_map;
	int		i;

	i = 0;
	flood_map = ft_calloc(1, sizeof(char *) * (msc->map->map_height + 1));
	if (!flood_map)
		error_message("Malloc failed\n", msc);
	while (i < msc->map->map_height)
	{
		flood_map[i] = ft_strdup(msc->map->map[i]);
		i++;
	}
	fill(flood_map, msc->map->plyr_y, msc->map->plyr_x);
	check_flooded_map(msc, flood_map);
	free_floodmap(flood_map);
}

void	free_floodmap(char **flood_map)
{
	int	i;

	i = 0;
	while (flood_map[i])
		free(flood_map[i++]);
	free(flood_map);
}
