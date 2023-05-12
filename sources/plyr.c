/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plyr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:36:09 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/12 14:44:36 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	position_player(t_masterstruc *masterstruc)
{
	int	i;
	int	j;

	j = 0;
	while (masterstruc->map->map[j])
	{
		i = 0;
		while (masterstruc->map->map[j][i])
		{
			if (masterstruc->map->map[j][i] == 'P')
			{
				masterstruc->map->plyr_y = j;
				masterstruc->map->plyr_x = i;
				return ;
			}
			i++;
		}
		j++;
	}
	error_message("Map Error: File doesn't contain a player", masterstruc);
}

void	player_one_move(t_masterstruc *msc, int x, int y)
{
	int	*moves;

	moves = ft_calloc(5, sizeof(int));
	if (!moves)
		error_message("Malloc failed\n", msc);
	if (x != msc->map->plyr_x || y != msc->map->plyr_y)
		ft_printf("# Moves: %d #\n", msc->moves++);
	if (msc->map->enemy_count == 1)
		enemy_patrol(msc->map, moves);
	else
		free(moves);
	if (msc->map->map[y][x] == 'P')
		msc->map->map[y][x] = '0';
	if (msc->map->map[y][x] == 'C')
	{
		msc->map->map[y][x] = '0';
		msc->map->map_collectible_count--;
	}
}

void	enemy_patrol(t_map *map, int *moves)
{
	pos_enemy(map);
	if (map->map[map->enemy_y - 1][map->enemy_x] == '0'
		|| map->map[map->enemy_y - 1][map->enemy_x] == 'P')
		moves[0] = 1;
	else
		moves[0] = 0;
	if (map->map[map->enemy_y + 1][map->enemy_x] == '0'
		|| map->map[map->enemy_y - 1][map->enemy_x] == 'P')
		moves[1] = 1;
	else
		moves[1] = 0;
	if (map->map[map->enemy_y][map->enemy_x - 1] == '0'
		|| map->map[map->enemy_y - 1][map->enemy_x] == 'P')
		moves[2] = 1;
	else
		moves[2] = 0;
	if (map->map[map->enemy_y][map->enemy_x + 1] == '0'
		|| map->map[map->enemy_y - 1][map->enemy_x] == 'P')
		moves[3] = 1;
	else
		moves[3] = 0;
	enemy_patrol_next_move(moves, map);
}

// 0 is up, 1 is down, 2 is left, 3 is right

void	enemy_patrol_next_move(int	*moves, t_map *map)
{
	int	rndm_nmb;

	srand(time(NULL));
	rndm_nmb = 4;
	while (moves[rndm_nmb] != 1)
		rndm_nmb = rand() % 4;
	if (rndm_nmb == 0)
		map->map[map->enemy_y - 1][map->enemy_x] = 'X';
	if (rndm_nmb == 1)
		map->map[map->enemy_y + 1][map->enemy_x] = 'X';
	if (rndm_nmb == 2)
		map->map[map->enemy_y][map->enemy_x - 1] = 'X';
	if (rndm_nmb == 3)
		map->map[map->enemy_y][map->enemy_x + 1] = 'X';
	map->enemy_y_old = map->enemy_y;
	map->enemy_x_old = map->enemy_x;
	map->map[map->enemy_y][map->enemy_x] = '0';
	free(moves);
}

void	pos_enemy(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'X')
			{
				map->enemy_y = j;
				map->enemy_x = i;
				return ;
			}
			i++;
		}
		j++;
	}
}
